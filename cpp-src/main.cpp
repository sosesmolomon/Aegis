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
    PerftResults results1;

    // b->loadFEN("r3k2r/p1ppqpb1/bn2pnN1/3P4/1p2P3/2N2Q1p/PPPBBPPP/R3K2R b KQkq - 0 1", game);
    b->loadFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R b KQkq - 0 1", game); // just rook attacking
    // b->loadFEN("r3k3/p1ppqpb1/bn2pnN1/3P4/1p2P2r/2N2Q1p/PPPBBPPP/R3K2R w KQq - 0 1", game); // just rook attacking
    printBoard(b, b->fullBoard());

    MoveList *possible_moves = new MoveList();
    MoveList *legals = new MoveList();

    b->genAllMoves(possible_moves, game);
    b->verifyLegalMoves(possible_moves, game, legals);

    makeMove(b, legals->at(39), game);
    printBoard(b, b->fullBoard());
    game->print();

    undoLastMove(b, game);
    printBoard(b, b->fullBoard());

    makeMove(b, moveStruct(h8, h4, ROOK, BLACK), game);
    printBoard(b, b->fullBoard());

    possible_moves->clear();
    legals->clear();

    b->genAllMoves(possible_moves, game);
    b->verifyLegalMoves(possible_moves, game, legals);

    legals->print();

    makeMove(b, legals->at(41), game);

    printBoard(b, b->fullBoard());

    exit(1);

    int depth = 3;

    // makeDefinedMove(b, moveStruct(b1, a3, KNIGHT, WHITE), possible_moves, game);
    // makeDefinedMove(b, moveStruct(h7, h6, PAWN, BLACK), possible_moves, game);
    // b->player ^= WHITE;

    printf("fdisljkfas nodes = %llu\n", b->perft(depth, game, results1));

    printf("-----------------------------------------------------------------------\n");

    PerftResults results;
    b->perftDivide(depth, game, results);

    std::cout << "Perft results at depth " << depth << ":\n";
    std::cout << "Nodes: " << results.nodes << "\n";
    std::cout << "Captures: " << results.captures << "\n";
    std::cout << "En Passant Captures: " << results.enPassantCaptures << "\n";
    std::cout << "Castles: " << results.castles << "\n";
    std::cout << "Promotions: " << results.promotions << "\n";
    std::cout << "Checks: " << results.checks << "\n";
    std::cout << "Discovered Checks: " << results.discoveredChecks << "\n";
    std::cout << "Double Checks: " << results.doubleChecks << "\n";
    std::cout << "Checkmates: " << results.checkmates << "\n";

    // printf("\nPAWNS:\n");
    // printBitString(b->pieceBB[PAWN]);

    // printf("\nBISHOP:\n");
    // printBitString(b->pieceBB[BISHOP]);

    // printf("\nKNIGHTS:\n");
    // printBitString(b->pieceBB[KNIGHT]);

    // printf("\nROOKS:\n");
    // printBitString(b->pieceBB[ROOK]);

    // printf("\nQUEEN:\n");
    // printBitString(b->pieceBB[QUEEN]);

    // printf("\nKING:\n");
    // printBitString(b->pieceBB[KING]);

    printBoard(b, b->fullBoard());

    game->print();

    exit(1);

    legals->print();

    // printf("isAttacked() = %d\n", b->isAttacked(king_sq, BLACK));
    // printf("isInCheck() = %d\n", b->isInCheck(WHITE));
    // printf("isInCheckmate() = %d\n", b->isInCheckmate(legal_moves_W, WHITE));
    // printf("%s isDefended() = %d by %s\n", sqToStr[f5], b->isDefended(king_sq, BLACK), colorToStr[BLACK]);
    b->player ^= WHITE;

    return 0;
}