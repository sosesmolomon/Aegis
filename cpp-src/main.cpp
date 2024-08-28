#include <cmath>
#include <stdio.h>
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

    b->initCBoard();
    initMagic(b);

    // move list for: 1. the game's current string of moves
    //                2. curren position: all of the possible moves to evalute
                            // or is this:
                                // attackBB[piece] -- where only legal moves are 1
    
    MoveList game_ml = MoveList();
    // ml.curr_idx = 0;

    MoveList possible_moves = MoveList();

    // b->setSq(ROOK, WHITE, c6);
    // b->setSq(BISHOP, WHITE, c3);
    // b->setSq(PAWN, WHITE, g7);
    
    b->genAllLegalMoves(&possible_moves, WHITE);
    possible_moves.print();
    printf("count = %d\n", possible_moves.size());
    return 0;
}
