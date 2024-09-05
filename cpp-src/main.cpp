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

void updateMoveListsW(CBoard *b, MoveList *possible_moves, MoveList *game)
{
    possible_moves->clear();
    b->legalAttackedSquares[WHITE].getBB() = 0ULL;
    b->genAllLegalMoves(possible_moves, game, WHITE);
    // removeChecks();
    // walk through the move list and determine if any of the moves results
    // in the current player being in check,
    // if they do, remove this from the movelist

    // if currently in check
    // walk through the movelist and remove anything that
    // doesn't take the player out of check

    // if moveList is 0, checkmate
}
void updateMoveListsB(CBoard *b, MoveList *possible_moves, MoveList *game)
{
    possible_moves->clear();
    b->legalAttackedSquares[BLACK].getBB() = 0ULL;
    b->genAllLegalMoves(possible_moves, game, BLACK);
    // removeChecks();
}

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

void makeRandomMoves(CBoard *b, MoveList *possible_moves, MoveList *game)
{
    int r;
    int counter = 0;
    printf("----------------------------------------------------\n");

    // printBitString(b->knightPosAttacks[g8], g8);
    // possible_moves->print();

    while (counter < 20) {
        updateMoveListsW(b, possible_moves, game);
        r = randomN(possible_moves->size() - 1);
        makeDefinedMove(b, possible_moves->at(r), possible_moves, game);

        printBoard(b, b->fullBoard());
        printf("----------------------------------------------------\n");

        updateMoveListsB(b, possible_moves, game);
        r = randomN(possible_moves->size() - 1);
        makeDefinedMove(b, possible_moves->at(r), possible_moves, game);
        printBoard(b, b->fullBoard());
        printf("----------------------------------------------------\n");

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

    b->initCBoard();
    // b->setSq(KNIGHT, WHITE, a3);
    // b->initTestBoard();
    initMagic(b);

    MoveList game = MoveList();

    MoveList possible_moves = MoveList();

    // game.print();

    // gen moves --> populates legalAttacks --> informs squareIsAttacked() --> know castling options
    b->genAllLegalMoves(&possible_moves, &game, WHITE);
    b->genAllLegalMoves(&possible_moves, &game, BLACK);
    possible_moves.clear();
    // --------------------------------------------------

    // reset white's attacked squares by regenerating moves
    updateMoveListsW(b, &possible_moves, &game);
    updateMoveListsB(b, &possible_moves, &game);

    // makeRandomMoves(b, &possible_moves, &game);
    // return 0;
    // possible_moves.print();

    updateMoveListsW(b, &possible_moves, &game);
    makeDefinedMove(b, moveStruct(e2, e4, PAWN, WHITE), &possible_moves, &game);

    updateMoveListsB(b, &possible_moves, &game);
    makeDefinedMove(b, moveStruct(e7, e5, PAWN, BLACK), &possible_moves, &game);

    updateMoveListsW(b, &possible_moves, &game);
    makeDefinedMove(b, moveStruct(g1, f3, KNIGHT, WHITE), &possible_moves, &game);

    updateMoveListsB(b, &possible_moves, &game);
    makeDefinedMove(b, moveStruct(b8, c6, KNIGHT, BLACK), &possible_moves, &game);

    updateMoveListsW(b, &possible_moves, &game);
    makeDefinedMove(b, moveStruct(f3, e5, KNIGHT, WHITE, true), &possible_moves, &game);

    updateMoveListsB(b, &possible_moves, &game);
    makeDefinedMove(b, moveStruct(c6, e5, KNIGHT, BLACK, true), &possible_moves, &game);

    printBoard(b, b->fullBoard());
    evaluatePosition(b);

    game.print();
    printf("here1\n");

    updateMoveListsW(b, &possible_moves, &game);
    std::vector<float> evals;

    printf("here\n");
    evals = *evaluateMoveList(b, &possible_moves, &game, &evals);
    printf("here2\n");
    printf("\n[");
    for (int i =0; i < evals.size(); i++) {
        printf("%f, ", evals.at(i));
    }
    printf("]\n\n");
    

    return 0; 
}

/*
TODO:
    position:
    - check checks... think about this. should this be a flag in the moveList? or more like a global variable...
    -

    engine:
        - basic 1 depth search -- find the next move with the best eval change
        - minimax search



*/