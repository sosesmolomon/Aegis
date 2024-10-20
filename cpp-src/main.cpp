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

// int randomN(int n)
// {
//     std::random_device rd;

//     // Initialize the Mersenne Twister random number generator
//     std::mt19937 gen(rd());

//     // Define a distribution to produce integers in the range [0, n]
//     std::uniform_int_distribution<> dist(0, n);

//     // Generate a random number in the range [0, n]
//     int randomNumber = dist(gen);
//     return randomNumber;
// }

// void makeDefinedMoves(CBoard *b, MoveList *possible_moves, MoveList *game)
// {
// }

// void makeRandomMoves(CBoard *b, MoveList *possible_moves, MoveList *game, int n)
// {
//     int r;
//     int counter = 0;
//     printf("----------------------------------------------------\n");

//     b->player = BLACK;
//     moveStruct m;

//     MoveList legal_moves_W = MoveList();
//     MoveList legal_moves_B = MoveList();

//     // printBitString(b->knightPosAttacks[g8], g8);
//     // possible_moves->print();

//     MoveList *legals;

//     std::vector<float> evals;

//     while (counter < n)
//     {
//         legals = (b->player == WHITE) ? &legal_moves_W : &legal_moves_B;
//         b->genAllLegalMoves(NULL, game, b->player ^ WHITE, true);
//         updateMoveLists(b, possible_moves, game, b->player, legals);

//         if (legals->size() == 0 && b->isInCheck(b->player))
//         {
//             printf("************************checkmate?*********************\n");
//             printBoard(b, b->fullBoard());
//             exit(1);
//         }
//         else if (legals->size() == 0)
//         {
//             printf("************************stalemate?*********************\n");
//             printBoard(b, b->fullBoard());
//             u64 tmp = b->legalAttackedSquares[b->player ^ WHITE];
//             printBitString(tmp);
//             printf("----------------------------------\n");
//             updateMoveLists(b, possible_moves, game, b->player ^ WHITE, legals);
//             printBitString(b->legalAttackedSquares[b->player ^ WHITE]);
//             printf("----------------------------------\n");
//             printBitString(b->legalAttackedSquares[b->player ^ WHITE] ^ tmp);
//             exit(1);
//         }

//         printf("size of legals = %lu\n", legals->size());
//         printf("evaluating for %s\n", colorToStr[b->player]);
//         r = bestMoveIndex(b, legals, game, b->player);
//         printf("best move at %d\n", r);
//         m = legals->at(r);

//         makeDefinedMove(b, m, legals, game);

//         printf("\n  %s %s | %s to %s", colorToStr[m.pC], pieceToStr[m.pT], sqToStr[m.from], sqToStr[m.to]);
//         if (m.isCapture)
//             printf(" **CAPTURE**");

//         if (m.isCastlingLong || m.isCastlingShort)
//             printf(" **CASTLING**");

//         if (m.isEnPassant)
//             printf(" **EN PASSANT**");

//         b->genAllLegalMoves(NULL, game, b->player, true);
//         if (b->isInCheck(b->player ^ WHITE))
//             printf(" **CHECK**");

//         printf("\n");

//         printBoard(b, b->fullBoard());

//         b->player ^= WHITE;
//         counter++;
//     }
// }

int main()
{
    CBoard board = CBoard();
    CBoard *b = &board;

    b->generatePiecePossibleMoves();
    initMagic(b);


    MoveList *game = new MoveList();
    MoveList *possible_moves = new MoveList();
    MoveList *legal_moves_W = new MoveList();
    MoveList *legal_moves_B = new MoveList(); 

    b->loadFEN("k3r3/1b5q/8/2n2p2/r3K3/8/8/8 w - - 0 1", game);
    // b->loadFEN("k7/8/8/5p2/4K3/8/8/8 w - - 0 1", game); // just pawn attacking
    // b->loadFEN("k3r3/8/8/8/4K3/8/8/8 w - - 0 1", game); // just rook attacking
    // b->loadFEN("k7/8/8/2n5/4K3/8/8/8 w - - 0 1", game); // just knight attacking
    
    u64 king = b->pieceBB[KING] & b->coloredBB[WHITE];
    int king_sq = firstOne( king );

    b->genAllMoves(possible_moves, game);
    printf("------------------ %s MOVES -------------------\n", colorToStr[b->player]);
    b->verifyLegalMoves(possible_moves, game, legal_moves_W);
    legal_moves_W->print();
    legal_moves_W->sort();

    // printf("isAttacked() = %d\n", b->isAttacked(king_sq, BLACK));
    // printf("isInCheck() = %d\n", b->isInCheck(WHITE));
    // printf("isInCheckmate() = %d\n", b->isInCheckmate(legal_moves_W, WHITE));
    // printf("%s isDefended() = %d by %s\n", sqToStr[f5], b->isDefended(king_sq, BLACK), colorToStr[BLACK]);
    b->player ^= WHITE;

    return 0;
}