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

void makeRandomMoves(CBoard *b, MoveList *possible_moves, MoveList *game, int n)
{
    int r;
    int counter = 0;
    printf("----------------------------------------------------\n");

    int color = WHITE;
    moveStruct m;

    // printBitString(b->knightPosAttacks[g8], g8);
    // possible_moves->print();

    while (counter < n)
    {
        updateMoveLists(b, possible_moves, game, color);
        r = randomN(possible_moves->size() - 1);
        m = possible_moves->at(r);
        makeDefinedMove(b, m, possible_moves, game);

        printf("\n  %s %s | %s to %s", colorToStr[m.pC], pieceToStr[m.pT], sqToStr[m.from], sqToStr[m.to]);
        if (m.isCapture)
            printf(" **CAPTURE**");
        
        if (m.isCastlingLong || m.isCastlingShort)
            printf(" **CASTLING**");

        if (m.isEnPassant)
            printf(" **EN PASSANT**");
        
        printf("\n");
            
        printBoard(b, b->fullBoard());

        color ^= WHITE;
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
    // b->initTestBoard();
    initMagic(b);

    MoveList game = MoveList();
    MoveList possible_moves = MoveList();

    // gen moves --> populates legalAttacks --> informs squareIsAttacked() --> know castling options
    b->genAllLegalMoves(&possible_moves, &game, WHITE);
    b->genAllLegalMoves(&possible_moves, &game, BLACK);
    possible_moves.clear();

    // reset white's attacked squares by regenerating moves
    updateMoveLists(b, &possible_moves, &game, BLACK);
    updateMoveLists(b, &possible_moves, &game, WHITE);

    makeRandomMoves(b, &possible_moves, &game, 60);

    for(int i =0; i < 60; i++) {
        undoLastMove(b, &game);
    }

    printBoard(b, b->fullBoard());

    return 0;

    possible_moves.print();
    updateMoveLists(b, &possible_moves, &game, WHITE);
    makeDefinedMove(b, moveStruct(e2, e4, PAWN, WHITE), &possible_moves, &game);

    updateMoveLists(b, &possible_moves, &game, BLACK);
    makeDefinedMove(b, moveStruct(e7, e5, PAWN, BLACK), &possible_moves, &game);

    updateMoveLists(b, &possible_moves, &game, WHITE);
    makeDefinedMove(b, moveStruct(g1, f3, KNIGHT, WHITE), &possible_moves, &game);

    updateMoveLists(b, &possible_moves, &game, BLACK);
    makeDefinedMove(b, moveStruct(b8, c6, KNIGHT, BLACK), &possible_moves, &game);

    updateMoveLists(b, &possible_moves, &game, WHITE);
    makeDefinedMove(b, moveStruct(f3, e5, KNIGHT, WHITE, true, 0, 0, 0, PAWN), &possible_moves, &game);

    updateMoveLists(b, &possible_moves, &game, BLACK);
    makeDefinedMove(b, moveStruct(c6, e5, KNIGHT, BLACK, true, 0, 0, 0, KNIGHT), &possible_moves, &game);

    updateMoveLists(b, &possible_moves, &game, WHITE);
    makeDefinedMove(b, moveStruct(b2, b3, PAWN, WHITE), &possible_moves, &game);

    updateMoveLists(b, &possible_moves, &game, BLACK);
    makeDefinedMove(b, moveStruct(g7, g6, PAWN, BLACK), &possible_moves, &game);

    updateMoveLists(b, &possible_moves, &game, WHITE);
    makeDefinedMove(b, moveStruct(c1, b2, BISHOP, WHITE), &possible_moves, &game);

    updateMoveLists(b, &possible_moves, &game, BLACK);
    makeDefinedMove(b, moveStruct(f8, g7, BISHOP, BLACK), &possible_moves, &game);

    // capture and undo
    updateMoveLists(b, &possible_moves, &game, WHITE);
    makeDefinedMove(b, moveStruct(b2, e5, BISHOP, WHITE, true, 0, 0, 0, KNIGHT), &possible_moves, &game);
    printBoard(b, b->fullBoard());

    updateMoveLists(b, &possible_moves, &game, BLACK);
    makeDefinedMove(b, moveStruct(g7, e5, BISHOP, BLACK, true, 0, 0, 0, BISHOP), &possible_moves, &game);

    printBoard(b, b->fullBoard());

    undoMove(b, game.at(game.size() - 1), &game);
    printBoard(b, b->fullBoard());
    undoMove(b, game.at(game.size() - 1), &game);
    printBoard(b, b->fullBoard());
    printf("---------------------------------------------------------------\n");

    // setup castling
    updateMoveLists(b, &possible_moves, &game, WHITE);
    makeDefinedMove(b, moveStruct(f1, a6, BISHOP, WHITE), &possible_moves, &game);

    updateMoveLists(b, &possible_moves, &game, BLACK);
    makeDefinedMove(b, moveStruct(g8, e7, KNIGHT, BLACK), &possible_moves, &game);

    printBoard(b, b->fullBoard());

    updateMoveLists(b, &possible_moves, &game, WHITE);
    possible_moves.print(33);
    makeDefinedMove(b, possible_moves.at(33), &possible_moves, &game);

    updateMoveLists(b, &possible_moves, &game, BLACK);
    makeDefinedMove(b, moveStruct(e8, a1, KING, BLACK, 0, 0, 1), &possible_moves, &game);

    printf("---------------------------------------------------------------\n");
    printBoard(b, b->fullBoard());
    printf("\n\nundo move:\n");
    game.print(game.size() - 1);
    undoLastMove(b, &game);
    printBoard(b, b->fullBoard());

    printf("\n\nundo move:\n");
    game.print(game.size() - 1);
    undoLastMove(b, &game);
    printBoard(b, b->fullBoard());

    game.print();

    // evaluatePosition(b);
    // printf("Best index for %s = %d\n", colorToStr[WHITE], bestMoveIndex(b, &possible_moves, &game, WHITE));

    return 0;
}

/*
TODO:
- theres a couple bugs happening:
- printBoard() shows a pawn when its clearly a queen -- this must be because of identifyPieceType
- setSq in undoMove is clearing the color and the piece at the end of the method... this clears the replaced queen
    - this is why the queen never comes back for the evaluation

*/