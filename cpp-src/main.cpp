#include <cmath>
#include <stdio.h>
#include <iostream>
#include <random>
#include "print.h"
#include "CBoard.h"
// #include "init.h"
#include "magic.h"
#include "move.h"
#include "bitboard.h"
#include "MoveList.h"
#include "utils.h"
#include "evaluate.h"
#include "engine.h"
// a1 - a8, b1, h1 - h8
//  0 - 7,  8,  56 - 63

int randomN(int n)
{
    std::random_device rd;

    // Initialize the Mersenne Twister random number generator
    std::mt19937 gen(rd());

    // Define a distribution to produce integers in the range [0, n]
    std::uniform_int_distribution<> dist(0, n);

    // Generate a random number in the range [0, n]
    int randomNumber = dist(gen);
    return randomNumber;
}

void makeDefinedMoves(CBoard *b, MoveList *possible_moves, MoveList *game)
{
}

void makeRandomMoves(CBoard *b, MoveList *possible_moves, MoveList *game, int n)
{
    int r;
    int counter = 0;
    printf("----------------------------------------------------\n");

    b->player = BLACK;
    moveStruct m;

    MoveList legal_moves_W = MoveList();
    MoveList legal_moves_B = MoveList();

    // printBitString(b->knightPosAttacks[g8], g8);
    // possible_moves->print();

    MoveList *legals;

    std::vector<float> evals;

    while (counter < n)
    {
        legals = (b->player == WHITE) ? &legal_moves_W : &legal_moves_B;
        b->genAllLegalMoves(NULL, game, b->player ^ WHITE, true);
        updateMoveLists(b, possible_moves, game, b->player, legals);

        if (legals->size() == 0 && b->isInCheck(b->player))
        {
            printf("************************checkmate?*********************\n");
            printBoard(b, b->fullBoard());
            exit(1);
        }
        else if (legals->size() == 0)
        {
            printf("************************stalemate?*********************\n");
            printBoard(b, b->fullBoard());
            u64 tmp = b->legalAttackedSquares[b->player ^ WHITE];
            printBitString(tmp);
            printf("----------------------------------\n");
            updateMoveLists(b, possible_moves, game, b->player ^ WHITE, legals);
            printBitString(b->legalAttackedSquares[b->player ^ WHITE]);
            printf("----------------------------------\n");
            printBitString(b->legalAttackedSquares[b->player ^ WHITE] ^ tmp);
            exit(1);
        }

        
        // r = randomN(legals->size() - 1);
        // m = legals->at(r);

        printf("size of legals = %lu\n", legals->size());
        printf("evaluating for %s\n", colorToStr[b->player]);
        r = bestMoveIndex(b, legals, game, b->player);
        printf("best move at %d\n", r);
        printf("size of legals = %lu\n", legals->size());
        m = legals->at(r);
        
        makeDefinedMove(b, m, legals, game);

        printf("\n  %s %s | %s to %s", colorToStr[m.pC], pieceToStr[m.pT], sqToStr[m.from], sqToStr[m.to]);
        if (m.isCapture)
            printf(" **CAPTURE**");

        if (m.isCastlingLong || m.isCastlingShort)
            printf(" **CASTLING**");

        if (m.isEnPassant)
            printf(" **EN PASSANT**");

        b->genAllLegalMoves(NULL, game, b->player, true);
        if (b->isInCheck(b->player ^ WHITE))
            printf(" **CHECK**");

        printf("\n");

        printBoard(b, b->fullBoard());

        b->player ^= WHITE;
        counter++;
    }
}

int main()
{
    CBoard board = CBoard();
    CBoard *b = &board;

    b->player = WHITE;
    b->inCheck[WHITE] = false;
    b->inCheck[BLACK] = false;

    b->atHomeCastleShort[WHITE] = true;
    b->atHomeCastleShort[BLACK] = true;

    b->atHomeCastleLong[WHITE] = true;
    b->atHomeCastleLong[BLACK] = true;

    // b->initCBoard();
    b->initTestBoard();
    initMagic(b);

    printBoard(b, b->fullBoard());

    MoveList game = MoveList();
    MoveList possible_moves = MoveList();
    MoveList legal_moves_W = MoveList();
    MoveList legal_moves_B = MoveList();

    MoveList *legal_moves;
    // important setup -- both colors know the other color's attacks
    b->genAllLegalMoves(NULL, &game, b->player, true);
    b->genAllLegalMoves(NULL, &game, b->player ^ WHITE, true);

    printBitString(b->legalAttackedSquares[b->player]);
    printBitString(b->legalAttackedSquares[b->player ^ WHITE]);

    makeRandomMoves(b, &possible_moves, &game, 10);

    return 0;

    printf("updating moves for %s\n", colorToStr[b->player]); // WHITE

    // updateMoveLists(b, &possible_moves, &game, b->player, (b->player == WHITE) ? &legal_moves_W : &legal_moves_B); // FOR BLACK
    b->genAllLegalMoves(NULL, &game, b->player ^ WHITE, true); // upate for BLACK
    printBitString(b->legalAttackedSquares[BLACK]);

    legal_moves = (b->player == WHITE) ? &legal_moves_W : &legal_moves_B;
    updateMoveLists(b, &possible_moves, &game, b->player, legal_moves); // FOR WHITE
    makeDefinedMove(b, legal_moves->at(0), legal_moves, &game);         // BLACK
    b->player ^= WHITE;                                                 // BLACK

    printBoard(b, b->fullBoard());

    legal_moves_B.print(0);
    printf("---------------------------------\n");
    legal_moves_W.print();
    printf("--------------------------------- %s\n", colorToStr[b->player]);

    return 0;

    updateMoveLists(b, &possible_moves, &game, b->player, (b->player == WHITE) ? &legal_moves_W : &legal_moves_B); // BLACK
    b->player ^= WHITE;

    legal_moves = (b->player == WHITE) ? &legal_moves_W : &legal_moves_B;
    legal_moves->print(0);
    return 0;

    updateMoveLists(b, &possible_moves, &game, b->player ^ WHITE, (b->player == WHITE) ? &legal_moves_W : &legal_moves_B);
    b->player ^= WHITE;

    makeRandomMoves(b, &possible_moves, &game, 60);

    return 0;
}

/*
TODO:
- theres a couple bugs happening:
- printBoard() shows a pawn when its clearly a queen -- this must be because of identifyPieceType
- setSq in undoMove is clearing the color and the piece at the end of the method... this clears the replaced queen
    - this is why the queen never comes back for the evaluation

*/