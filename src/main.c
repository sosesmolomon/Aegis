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

// void capture
// make move simply moves a piece on it's own bitboard
// capture needs to turn off the piece that has been captured on that bitboard

int main()
{
    int **scalarArrays = initScalarArrayPointers();
    Board *board = initBitBoards();
    Board *test_board = initTestBoards();
    player_color curr_player = WHITE;

    // uncomment for testing mode
    board = test_board;

    // Board fake_board = *board;
    // makeMove(&fake_board, 59, 1, KING, WHITE);
    // printBitString(fullBitBoard(&fake_board));
    // printBitString(fullBitBoard(board));

    int index = 0;

    // isInCheck(board, curr_player);

    // pawnOnHomeRow(&curr_player, 63);
    // findMoves(board, PAWN, &curr_player, 63, true);
    // printPossibleMoves(pawn_moves, 63);
    // return 0;

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

    // printBitString(fullBitBoard(board));
    // printf("num of pawns = %d", pieceCount(board->pawn_W));
    // makeMove(board, 3, 48, ROOK, BLACK);
    // printf("num of pawns = %d", pieceCount(board->pawn_W));
    // return 0;

    possible_move *all_moves;
    // valid options =  where color == current player

    curr_player = BLACK;

    all_moves = getAllMovesFromCurrentBoard(board, curr_player, scalarArrays);

    bool print = isInCheck(board, curr_player, all_moves);
    if (print)
        printf("IN CHECK");
    else
        printf("NOT IN CHECK");

    int move_index = 0;

    int white_best_eval = -1000;
    int black_best_eval = 1000;
    int best_index = 0;

    while (all_moves[move_index].piece != NONE && move_index < 256)
    {
        // printf("start = %d, index = %d\n", all_moves[move_index].start, move_index);
        printf("\n{ \n start = %s \n end = %s\n type = %s \n color = %s \n eval_change = %f\n} index = %d \n", square_names[all_moves[move_index].start], square_names[all_moves[move_index].start + all_moves[move_index].shift], piece_str[all_moves[move_index].piece], (all_moves[move_index].color == WHITE) ? "WHITE" : "BLACK", all_moves[move_index].eval_after_move, move_index);

        // get and make best move for curr_player
        if (all_moves[move_index].color == curr_player)
        {

            // eval change really.
            if (all_moves[move_index].eval_after_move < black_best_eval)
            {
                best_index = move_index;
            }
        }
        move_index++;
    };

    int best_start = all_moves[best_index].start;
    int best_shift = all_moves[best_index].shift;
    piece_type piece = all_moves[best_index].piece;
    player_color color = all_moves[best_index].color;
    printf("old board eval: %d \n", evaluateBoard(board, scalarArrays));
    makeMove(board, best_start, best_shift, piece, color);
    printf("new board eval: %d \n", evaluateBoard(board, scalarArrays));
    printBitString(fullBitBoard(board));

    printf("----------------------------------------\n");

    curr_player = WHITE;
    all_moves = getAllMovesFromCurrentBoard(board, curr_player, scalarArrays);

    move_index = 0;
    while (all_moves[move_index].piece != NONE && move_index < 256)
    {
        printf("\n{ \n start = %s \n end = %s\n type = %s \n color = %s \n eval_change = %f\n} index = %d \n", square_names[all_moves[move_index].start], square_names[all_moves[move_index].start + all_moves[move_index].shift], piece_str[all_moves[move_index].piece], (all_moves[move_index].color == WHITE) ? "WHITE" : "BLACK", all_moves[move_index].eval_after_move, move_index);
        if (all_moves[move_index].color == curr_player)
        {
            // printf("start = %d, index = %d\n", all_moves[move_index].start, move_index);

            // eval change really.
            if (all_moves[move_index].eval_after_move > white_best_eval)
            {
                best_index = move_index;
            }
        }

        move_index++;
    }

    print = isInCheck(board, curr_player, all_moves);
    if (print)
        printf("IN CHECK");
    else
        printf("NOT IN CHECK");

    best_start = all_moves[best_index].start;
    best_shift = all_moves[best_index].shift;
    piece = all_moves[best_index].piece;
    color = all_moves[best_index].color;

    printf("old board eval: %d \n", evaluateBoard(board, scalarArrays));
    makeMove(board, best_start, best_shift, piece, color);
    printf("new board eval: %d \n", evaluateBoard(board, scalarArrays));
    printBitString(fullBitBoard(board));

    print = isInCheck(board, curr_player, all_moves);
    if (print)
        printf("IN CHECK");
    else
        printf("NOT IN CHECK");

    free(all_moves);

    free(board);

    free(scalarArrays);

    return 0;
}