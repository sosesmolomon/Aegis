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

int main()
{
    CBoard board = CBoard();
    CBoard *b = &board;

    b->generatePiecePossibleMoves();
    initMagic(b);

    MoveList *game = new MoveList();
    MoveList all;
    MoveList legal;

    // std::string fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"; // original
    // std::string fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/Pp2P3/2N2Q1p/1PPBBPPP/R3K2R b KQkq a3 0 1"; // a2 - a4
    // std::string fen =  "r3k2r/p1ppqpb1/1n2pnp1/3PN3/Pp2P3/2N2Q1p/1PPBbPPP/R3K2R w KQkq - 0 1"; //a6 - e2
    std::string fen =  "n1n5/PPPk4/8/8/8/8/4Kppp/5N1N b - - 0 1"; // promotions.
    int depth = 6;

    b->loadFEN(fen, game);

   
    // // lets make promotions work
    /*

    b->genAllMoves(&all, game);
    b->verifyLegalMoves(&all, game, &legal);

    makeDefinedMove(b, moveStruct(a2, a3, PAWN, WHITE), &legal, game);
    
    b->player ^= WHITE;
    legal.clear();
    all.clear();
   

    b->genAllMoves(&all, game);
    b->verifyLegalMoves(&all, game, &legal);

    makeDefinedMove(b, moveStruct(d7, d6, PAWN, BLACK, 0, 0, 0), &legal, game);
    
    b->player ^= WHITE;
    legal.clear();
    all.clear();

    b->genAllMoves(&all, game);
    b->verifyLegalMoves(&all, game, &legal);

    makeDefinedMove(b, moveStruct(e2, b5, BISHOP, WHITE), &legal, game);
    
    b->player ^= WHITE;
    legal.clear();
    all.clear();
    

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

    // perft()
    // game->clear();
    // b->clearBoard();

    */


    
    PerftResults results1;

    printf("perft for %s at board = ", colorToStr[b->player]);
    printBoard(b, b->fullBoard());
    for (int i = 0; i < depth; i++)
    {
        printf("nodes = %llu\n", b->perft(i, game, results1));
    }

    // reset for perftDivide()
    printf("-----------------------------------------------------------------------\n");
    game->clear();


    CBoard board2 = CBoard();
    CBoard *b2 = &board2;
    

    b2->generatePiecePossibleMoves();
    initMagic(b2);

    b2->loadFEN(fen, game);
    
    /*
    b2->genAllMoves(&all, game);
    b2->verifyLegalMoves(&all, game, &legal);

    makeDefinedMove(b2, moveStruct(a2, a3, PAWN, WHITE), &legal, game);

    b2->player ^= WHITE;
    legal.clear();
    all.clear();


    b2->genAllMoves(&all, game);
    b2->verifyLegalMoves(&all, game, &legal);

   
    makeDefinedMove(b2, moveStruct(d7, d6, PAWN, BLACK, 0, 0, 0), &legal, game);
    legal.clear();
    all.clear();
    b2->player ^= WHITE;


    b2->genAllMoves(&all, game);
    b2->verifyLegalMoves(&all, game, &legal);

    makeDefinedMove(b2, moveStruct(e2, b5, BISHOP, WHITE), &legal, game);
    
    b2->player ^= WHITE;
    legal.clear();
    all.clear();
    */


    // exit(1);


    // perftDivide()
    printf("perft for %s at board = ", colorToStr[b2->player]);
    printBoard(b2, b2->fullBoard());

    PerftResults results;
    b->perftDivide(depth - 1, game, results);

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


    printBoard(b, b->fullBoard());
    game->print();

    exit(1);

    // printf("isAttacked() = %d\n", b->isAttacked(king_sq, BLACK));
    // printf("isInCheck() = %d\n", b->isInCheck(WHITE));
    // printf("isInCheckmate() = %d\n", b->isInCheckmate(legal_moves_W, WHITE));
    // printf("%s isDefended() = %d by %s\n", sqToStr[f5], b->isDefended(king_sq, BLACK), colorToStr[BLACK]);
    b->player ^= WHITE;

    return 0;
}