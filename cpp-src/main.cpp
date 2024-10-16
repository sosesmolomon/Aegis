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

    // test
    // b->loadFEN("4k2r/6r1/8/8/8/8/3R4/R3K3 w Qk - 0 1");

    // Normal board setup
    // b->loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    // En Passant setup
    // b->loadFEN("8/1p6/8/2P5/8/8/8/8 w - b6 0 1");

    // Legal castling setup
    // b->loadFEN("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");

    // Illegal castling through check setup
    b->loadFEN("5rk1/8/8/8/8/8/8/4K2R w K - 0 1");
    exit(1);

    // Stalemate setup
    b->loadFEN("7k/5Q2/6Q1/8/8/8/8/7K b - - 0 1");

    // Checkmate setup
    b->loadFEN("7k/5Q2/8/8/8/8/8/7K b - - 0 1");
    
    exit(1);

    b->initCBoard();
    initMagic(b);


    printBitString(0b000100000000000000000000000000000000000000000000000000000001000);
    printBitString(b->pieceBB[QUEEN]);
    exit(1);

    MoveList *game = new MoveList();
    MoveList *possible_moves = new MoveList();
    MoveList *legal_moves_W = new MoveList();
    MoveList *legal_moves_B = new MoveList();

    // b->fillAttackBBs(game, UINT64_MAX ^ b->coloredBB[BLACK], BLACK);
    // for (int i = 0; i < 6; i++) {
    //     printf("%s:\n", pieceToStr[i]);
    //     printBitString(b->pieceAttacks[BLACK][i]);
    // }

    b->genAllMoves(possible_moves, game, b->player);
    printf("--------------\n");
    b->verifyLegalMoves(possible_moves, game, b->player, legal_moves_W);
    legal_moves_W->print();
    legal_moves_W->sort();

    b->player^=WHITE;

    return 0;
}