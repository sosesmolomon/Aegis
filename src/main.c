#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typedefs.h"
#include "utils.h"
#include "print.h"
#include "init.h"
#include "move.h"

const char *const piece_str[] =
    {
        [NONE] = "NONE",
        [PAWN] = "PAWN",
        [BISHOP] = "BISHOP",
        [KNIGHT] = "KNIGHT",
        [ROOK] = "ROOK",
        [QUEEN] = "QUEEN",
        [KING] = "KING"};

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

typedef struct possible_move
{
    int start;
    int shift;
    piece_type piece;
    float eval_after_move;
} possible_move;

void makeMove(uint64_t *bitboard, int start, int shift, piece_type piece, player_color *curr)
{
    printf("making move");
    uint64_t mask = 1ULL << (start + shift);
    mask = mask | 1ULL << start;
    printf("\n");
    printBitString(mask);
    *bitboard = *bitboard ^ mask;
}

int main()
{
    int **scalarArrays = initScalarArrayPointers();
    Board *board = initBitBoards();
    Board *test_board = initTestBoards();
    player_color curr_player = WHITE;

    // uncomment for testing mode
    board = test_board;

    piece_type curr_piece;
    uint64_t square = 1ULL;

    // lets say there's 256 possible moves on a single player's turn
    int index = 0;

    // pawnOnHomeRow(&curr_player, 63);
    // findMoves(board, PAWN, &curr_player, 63, true);
    // printPossibleMoves(pawn_moves, 63);
    // return 0;

    possible_move *all_curr_player_moves = (possible_move *)malloc(sizeof(possible_move) * 256);
    int move_index = 0;
    // TODO:
    //  check for Checks -- canCapture?
    //  check for castling
    //

    // makeMove(*board->pieceBB, start, end)
    // evaluatePositionAfterMove()
    // undoMove()
    // makeNextMove()

    // printf("\n");
    // makeMove(&board->pawn_W, 55, -16, PAWN, &curr_player);
    // printf("\n");
    // printBitString(fullBitBoard(board));

    for (int i = 0; i < 56; i++)
    {
        curr_piece = identifyPieceType(square, board, &curr_player);

        // finds all of the moves for this piece

        findMoves(board, curr_piece, &curr_player, i, false);
        // printPossibleMoves(pawn_moves, i);
        square = square << 1;

        if (curr_piece != NONE)
        {
            int *moves;
            int moves_count;
            switch (curr_piece)
            {
            case PAWN:
                moves = pawn_moves;
                moves_count = 4;
                break;
            case BISHOP:
                moves = bishop_moves;
                moves_count = 28;

                break;
            case KNIGHT:
                moves = knight_moves;
                moves_count = 8;

                break;
            case ROOK:
                moves = rook_moves;
                moves_count = 28;

                break;
            case QUEEN:
                moves = queen_moves;
                moves_count = 56;
                printf("THIS IS A QUEEN");

                break;
            case KING:
                moves = king_moves;
                moves_count = 8;

                break;
            case NONE:
                break;
            }

            int index = 0;

            while (moves[index] != 0 && index < moves_count)
            {
                all_curr_player_moves[move_index].start = i;

                all_curr_player_moves[move_index].shift = moves[index];

                all_curr_player_moves[move_index].piece = curr_piece;

                // makeMove()
                all_curr_player_moves[move_index].eval_after_move = evaluateBoard(board, scalarArrays);

                move_index++;
                index++;
            }

            free(moves);
        }

        // switch (curr_piece)
        // {
        // case PAWN:
        //     free(pawn_moves);
        //     break;
        // case BISHOP:
        //     free(bishop_moves);
        //     break;
        // case KNIGHT:
        //     free(knight_moves);
        //     break;
        // case ROOK:
        //     free(rook_moves);
        //     break;
        // case QUEEN:
        //     free(queen_moves);
        //     break;
        // case KING:
        //     free(king_moves);
        //     break;
        // case NONE:
        //     break;
        // }

        // we now have all of the possible moves:

        // i could save each possible move as [ start_position, piece_type, shift, TBD_eval(),  ]

        // for (int i = 0; i < 56 && (pawn_moves[i] != 0); i++)
        // {
        //     all_curr_player_moves[index] = pawn_moves[i];
        //     index++;
        // }
        // for (int i = 0; i < 56 && (bishop_moves[i] != 0); i++)
        // {
        //     all_curr_player_moves[index] = bishop_moves[i];
        //     index++;
        // }
        // for (int i = 0; i < 56 && (knight_moves[i] != 0); i++)
        // {
        //     all_curr_player_moves[index] = knight_moves[i];
        //     index++;
        // }
        // for (int i = 0; i < 56 && (rook_moves[i] != 0); i++)
        // {
        //     all_curr_player_moves[index] = rook_moves[i];
        //     index++;
        // }
        // for (int i = 0; i < 56 && (queen_moves[i] != 0); i++)
        // {
        //     all_curr_player_moves[index] = queen_moves[i];
        //     index++;
        // }
        // for (int i = 0; i < 56 && (king_moves[i] != 0); i++)
        // {
        //     all_curr_player_moves[index] = king_moves[i];
        //     index++;
        // }
    }
    move_index = 0;

    while (all_curr_player_moves[move_index].piece != NONE)
    {
        printf("\n{ \n start = %d \n shift = %d\n type= %s \n eval= %f\n}", all_curr_player_moves[move_index].start, all_curr_player_moves[move_index].shift, piece_str[all_curr_player_moves[move_index].piece], all_curr_player_moves[move_index].eval_after_move);
        move_index++;
    };

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