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

    
        printf("size of legals = %lu\n", legals->size());
        printf("evaluating for %s\n", colorToStr[b->player]);
        r = bestMoveIndex(b, legals, game, b->player);
        printf("best move at %d\n", r);
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

    MoveList *game = new MoveList();
    MoveList *possible_moves = new MoveList();
    MoveList *legal_moves_W = new MoveList();
    MoveList *legal_moves_B = new MoveList();

    // important setup -- both colors know the other color's attacks
    // b->genAllLegalMoves(NULL, &game, b->player, true);
    // b->genAllLegalMoves(NULL, &game, b->player ^ WHITE, true);

    b->fillAttackBBs(game, UINT64_MAX, WHITE);
    for (int i = 0; i < 6; i++) {
        printf("%s:\n", pieceToStr[i]);
        printBitString(b->pieceAttacks[b->player][i]);
    }

    b->genPawnMoves(possible_moves, game, UINT64_MAX, BLACK);
    makeMove(b, moveStruct(f7, f6, PAWN, BLACK), game);
    makeMove(b, moveStruct(d7, d5, PAWN, BLACK), game);

    makeMove(b, moveStruct(e5, d6, PAWN, WHITE, 1, 1), game);
    makeMove(b, moveStruct(d6, d7, PAWN, WHITE), game);

    possible_moves->clear();
    b->genPawnMoves(possible_moves, game, UINT64_MAX, WHITE);
    possible_moves->print();



    // printBoard(b, b->fullBoard());

    // possible_moves->clear();
    // b->genPawnMoves(possible_moves, game, UINT64_MAX, WHITE);
    // possible_moves->print();

    // printBitString(0xFFUL << a8);
    return 0;
}
