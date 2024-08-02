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

int bishopMoves[] = {9, 18, 27, 36, };
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

    int *pawn_moves = (int *)malloc(sizeof(int) * 4);
    int *bishop_moves = (int *)malloc(sizeof(int) * 32);
    int *knight_moves = (int *)malloc(sizeof(int) * 8);

    for (int i = 0; i < 64; i++)
    {
        curr_piece = identifyPieceType(square, board, &curr_player);

        switch (curr_piece)
        {
        case NONE:
            break;
        case PAWN:
            pawn_moves = findPawnMoves(board, pawn_moves, square, &curr_player, i);
            printf("\n");
            printf("Possible moves for Pawn at position %d: ", i);
            for (int j = 0; j < 4; j++)
            {
                printf("%d, ", pawn_moves[j]);
            }
            printf("\n");
            // printf("position = %d ", i);
            // printPossibleMoves(square, pawn_moves, i);
            break;
        case BISHOP:
            findBishopMoves(board, bishop_moves, square, &curr_player, i);
            break;
        case KNIGHT:
            printf("knight");
            knight_moves = findKnightMoves(board, knight_moves, square, &curr_player, i);
            printf("\n");
            printf("Possible moves for Knight at position %d: ", i);
            for (int j = 0; j < 8; j++)
            {
                printf("%d, ", knight_moves[j]);
            }
            printf("\n");
            uint64_t show = 1ULL << i;
            // printBitString(show);
            for (int j = 0; j < 8; j++)
            {
                show = show | (1ULL << (i + (knight_moves[j])));
            }
            printBitString(show);

            break;
        case ROOK:
            findRookMoves();
            break;
        case QUEEN:
            findQueenMoves();
            break;
        case KING:
            findKingMoves();
            break;
        default:
            break;
        }

        square = square << 1;
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