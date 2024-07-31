#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typedefs.h"
#include "utils.h"
#include "print.h"
#include "init.h"

int pawn_value = 10;
int knight_value = 30;
int bishop_value = 30;
int rook_value = 50;
int queen_value = 90;

// 0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000001
//   (1 << 63)                                                                           (1 << 0)
//    a1    a8                                                                g8 h1     h8

int horseMoves[] = {-17, -15, -10, -6, 6, 10, 15, 17};

/*

printed from printBitString LEFT SHIFTING
00000000 (7 - 0) (h1 - h8)
00000000 (15 - 8)
00000000 (23 - 16)
00000000 (31 - 24)
00000000 (39 - 32)
00000000 (47 - 40)
00000000 (55 - 48)
00000000 (63 - 56) (a1 - a8)

0b(pos63, pos62, ..., pos1, pos0)

*/

// TODO: create adjustment multiplier boards to evaluate positions
/*
void adjust_evaluations() {
    // board = h1 g1 f1 ... a1 h2 g2 ... c8 b8 a8


    int white_pawn_adj[] = {
        10, 10, 10, 10, 10, 10, 10, 10,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    int white_pawn_adj[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    int white_pawn_adj[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    int white_pawn_adj[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

}
*/

/*
init:


*/

int main()
{
    int** scalarArrays = initScalarArrayPointers();
    Board *board = initBitBoards();
    Board *test_board = initTestBoards();
    // color player = WHITE;

    // uncomment for testing mode
    // board = test_board;

    evaluateBoard(board, scalarArrays);

    // after everything is setup. the boards are initialized.

    // WHITES TURN

    // board evaluation:
    // Rook has a base value of 5
    // a rook on the 7th rank is huge, say

    // choosing a next move, what I need to know:
    // 1. all possible and legal moves [] -- not where a same color piece resides, or off the board
    // 2. the evaluation

    free(board);
    // free(scalarArrays[PAWN]);
    // free(scalarArrays[BISHOP]);
    // free(scalarArrays[KNIGHT]);
    // free(scalarArrays[ROOK]);
    // free(scalarArrays[KING]);
    // free(scalarArrays[QUEEN]);
    free(scalarArrays);

    return 0;
}