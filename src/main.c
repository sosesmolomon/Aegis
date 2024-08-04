#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typedefs.h"
#include "utils.h"
#include "print.h"
#include "init.h"
#include "move.h"

int pawn_value = 10;
int knight_value = 30;
int bishop_value = 30;
int rook_value = 50;
int queen_value = 90;

// 0b 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000001
//   (1 << 63)                                                                           (1 << 0)
//    a1    a8                                                                g8 h1     h8

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
    int **scalarArrays = initScalarArrayPointers();
    Board *board = initBitBoards();
    Board *test_board = initTestBoards();
    player_color curr_player = WHITE;

    // uncomment for testing mode
    board = test_board;

    piece_type curr_piece;
    uint64_t curr_bitboard;
    uint64_t square = 1ULL;

    // lets say there's 256 possible moves on a single player's turn
    int index = 0;

    // pawnOnHomeRow(&curr_player, 63);
    // findMoves(board, PAWN, &curr_player, 63, true);
    // printPossibleMoves(pawn_moves, 63);
    // return 0;

    int *all_curr_player_moves = (int*)malloc(sizeof(int) * 256);
    
    for (int i = 0; i < 64; i++)
    {
        curr_piece = identifyPieceType(square, board, &curr_player);
        findMoves(board, curr_piece, &curr_player, i, false);
        printPossibleMoves(pawn_moves, i);
        square = square << 1;


        for (int i = 0; i < 56 && (pawn_moves[i] != 0); i++)
        {
            all_curr_player_moves[index] = pawn_moves[i];
            index++;
        }
        for (int i = 0; i < 56 && (bishop_moves[i] != 0); i++)
        {
            all_curr_player_moves[index] = bishop_moves[i];
            index++;
        }
        for (int i = 0; i < 56 && (knight_moves[i] != 0); i++)
        {
            all_curr_player_moves[index] = knight_moves[i];
            index++;
        }
        for (int i = 0; i < 56 && (rook_moves[i] != 0); i++)
        {
            all_curr_player_moves[index] = rook_moves[i];
            index++;
        }
        for (int i = 0; i < 56 && (queen_moves[i] != 0); i++)
        {
            all_curr_player_moves[index] = queen_moves[i];
            index++;
        }
        for (int i = 0; i < 56 && (king_moves[i] != 0); i++)
        {
            all_curr_player_moves[index] = king_moves[i];
            index++;
        }        


        free(pawn_moves);
        free(bishop_moves);
        free(knight_moves);
        free(rook_moves);
        free(queen_moves);
        free(king_moves);
    }

      for (int i = 0; i < 256 && (all_curr_player_moves[i] != 0); i++)
        {
            printf("%d, ", all_curr_player_moves[i]);
        }


    // findPawnMoves(board->pawn_W, &curr_player);

    // evaluateBoard(board, scalarArrays);

    // after everything is setup. the boards are initialized.

    // WHITES TURN

    // board evaluation:
    // Rook has a base value of 5
    // a rook on the 7th rank is huge, say

    // choosing a next move, what I need to know:
    // 1. all possible and legal moves [] -- not where a same color piece resides, or off the board
    // 2. the evaluation

    free(board);

    free(scalarArrays);

    return 0;
}