#include <cmath>
#include <stdio.h>
#include <iostream>
#include "print.h"
#include "CBoard.h"
// #include "init.h"
#include "magic.h"
#include "move.h"
#include "bitboard.h"
#include "MoveList.h"
#include "utils.h"
// a1 - a8, b1, h1 - h8
//  0 - 7,  8,  56 - 63

int main()
{
    CBoard board = CBoard();
    CBoard *b = &board;

    // b->initCBoard();
    b->initTestBoard();
    initMagic(b);

    MoveList game_ml = MoveList();

    MoveList possible_moves = MoveList();

    game_ml.print();

    // b->setSq(PAWN, WHITE, a5);
    // b->setSq(KNIGHT, BLACK, h3);

    // gen moves --> populates legalAttacks --> informs squareIsAttacked() --> know castling options
    b->genAllLegalMoves(&possible_moves, &game_ml, WHITE);
    b->genAllLegalMoves(&possible_moves, &game_ml, BLACK);
    possible_moves.clear();
    // --------------------------------------------------

    // reset white's attacked squares by regenerating moves
    b->legalAttackedSquares[WHITE].getBB() = 0ULL;
    b->genAllLegalMoves(&possible_moves, &game_ml, WHITE);

    b->legalAttackedSquares[BLACK].getBB() = 0ULL;
    b->genAllLegalMoves(&possible_moves, &game_ml, BLACK);

    possible_moves.print();

    makeMove(b, possible_moves.at(10), &game_ml);

    possible_moves.clear();
    b->legalAttackedSquares[WHITE].getBB() = 0ULL;
    b->genAllLegalMoves(&possible_moves, &game_ml, WHITE);

    b->legalAttackedSquares[BLACK].getBB() = 0ULL;
    b->genAllLegalMoves(&possible_moves, &game_ml, BLACK);
    possible_moves.print();

    makeMove(b, possible_moves.at(1), &game_ml);
    printBoard(b, b->fullBoard());

    possible_moves.print(1);


    undoMove(b, possible_moves.at(1), &game_ml);
    printBoard(b, b->fullBoard());

    return 0;
}
