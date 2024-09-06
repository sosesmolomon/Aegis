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

void makeRandomMoves(CBoard *b, MoveList *possible_moves, MoveList *game)
{
    int r;
    int counter = 0;
    printf("----------------------------------------------------\n");

    // printBitString(b->knightPosAttacks[g8], g8);
    // possible_moves->print();

    while (counter < 20)
    {
        updateMoveLists(b, possible_moves, game, WHITE);
        r = randomN(possible_moves->size() - 1);
        makeDefinedMove(b, possible_moves->at(r), possible_moves, game);

        printBoard(b, b->fullBoard());
        printf("----------------------------------------------------\n");

        updateMoveLists(b, possible_moves, game, BLACK);
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
    updateMoveLists(b, &possible_moves, &game, WHITE);
    updateMoveLists(b, &possible_moves, &game, BLACK);

    // makeRandomMoves(b, &possible_moves, &game);
    // return 0;
    // possible_moves.print();

    updateMoveLists(b, &possible_moves, &game, WHITE);
    makeDefinedMove(b, moveStruct(e2, e4, PAWN, WHITE), &possible_moves, &game);

    updateMoveLists(b, &possible_moves, &game, BLACK);
    makeDefinedMove(b, moveStruct(e7, e5, PAWN, BLACK), &possible_moves, &game);

    updateMoveLists(b, &possible_moves, &game, WHITE);
    makeDefinedMove(b, moveStruct(g1, f3, KNIGHT, WHITE), &possible_moves, &game);

    updateMoveLists(b, &possible_moves, &game, BLACK);
    makeDefinedMove(b, moveStruct(b8, c6, KNIGHT, BLACK), &possible_moves, &game);

    updateMoveLists(b, &possible_moves, &game, WHITE);
    makeDefinedMove(b, moveStruct(f3, e5, KNIGHT, WHITE, true), &possible_moves, &game);

    updateMoveLists(b, &possible_moves, &game, BLACK);
    makeDefinedMove(b, moveStruct(c6, e5, KNIGHT, BLACK, true), &possible_moves, &game);


    game.print();

    b->setSq(QUEEN, BLACK, h3);    
    printBoard(b, b->fullBoard());

    updateMoveLists(b, &possible_moves, &game, WHITE);
    possible_moves.print();
    std::vector<float> evals;

    // printf("here\n");
    // evals = *evaluateMoveList(b, &possible_moves, &game, &evals);

    // printf("here2\n");
    // printf("\n[");
    // for (int i = 0; i < evals.size(); i++)
    // {
    //     printf("%f, ", evals.at(i));
    // }
    // printf("]\n\n");

    evaluatePosition(b);
    printf("Best index for %s = %d\n", colorToStr[WHITE], bestMoveIndex(b, &possible_moves, &game, WHITE));

    return 0;
}

/*
TODO:
- theres a couple bugs happening:
- printBoard() shows a pawn when its clearly a queen -- this must be because of identifyPieceType
- setSq in undoMove is clearing the color and the piece at the end of the method... this clears the replaced queen
    - this is why the queen never comes back for the evaluation

*/