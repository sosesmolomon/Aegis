#include <stdlib.h>
#include <math.h>

#include "init.h"
#include "print.h"
#include "CBoard.h"
#include "utils.h"

u64 emptyEdges = 0b1111111110000001100000011000000110000001100000011000000111111111;

CBoard *initCBoard()
{
    CBoard *board = new CBoard();

    // board->bishopPosAttacks = new u64[64];
    // board->rookPosAttacks = new u64[64];

    generatePiecePossibleMoves(board);

    // for (int i = 0; i < 64; i++)
    // {
    //     lookup_u64[i] = (1ULL << i);
    // }

    board->pieceBB[PAWN] = 0xFFUL << a2 | 0xFFUL << a7;
    board->pieceBB[BISHOP] = (1ULL << c1) | (1ULL << f1) | (1ULL << c8) | (1ULL << g8);
    board->pieceBB[KNIGHT] = (1ULL << b1) | (1ULL << g1) | (1ULL << b8) | (1ULL << g8);
    board->pieceBB[ROOK] =  (1ULL << a1) | (1ULL << h1) | (1ULL << a8) | (1ULL << h8) ;
    board->pieceBB[QUEEN] = (1ULL << d1) | (1ULL << d8);
    board->pieceBB[KING] = (1ULL << e1) | (1ULL << e8);

    board->coloredBB[WHITE] = 0xFFFFUL;
    board->coloredBB[BLACK] = 0xFFFFUL << a7;

        // board->bishop_W = (1ULL << 61) | (1ULL << 58);
        // board->knight_W = (1ULL << 62) | (1ULL << 57);
        // board->rook_W = (1ULL << 63) | (1ULL << 56);
        // board->queen_W = 1ULL << 60;
        // board->king_W = 1ULL << 59;

        // board->pawn_B = 0xFFUL << 8; // takes 0b0000000000000000000000000000000000000000000000000000000011111111 --> 0b0000000000000000000000000000000000000000000000001111111100000000
        // board->bishop_B = (1ULL << 2) | (1ULL << 5);
        // board->knight_B = (1ULL << 1) | (1ULL << 6);
        // board->rook_B = (1ULL << 0) | (1ULL << 7);
        // board->queen_B = 1ULL << 4;
        // board->king_B = 1ULL << 3;

        return board;
}

void removeAttackEdges(CBoard *board)
{
    for (int i = 0; i < 64; i++)
    {
        board->bishopPosAttacks[i] ^= emptyEdges & board->bishopPosAttacks[i];
    }
}

int bishopMoves[4][7] = {{7, 14, 21, 28, 35, 42, 49}, {-7, -14, -21, -28, -35, -42, -49}, {9, 18, 27, 36, 45, 54, 63}, {-9, -18, -27, -36, -45, -54, -63}};
bool isLegalBishopMove(int start, int end)
{
    int start_row, start_col, end_row, end_col, dX, dY;
    start_row = floor(start / 8);
    start_col = start % 8;

    end_row = floor(end / 8);
    end_col = end % 8;

    dX = abs(start_col - end_col);
    dY = abs(start_row - end_row);

    if (dX == dY)
        return true;
    else
        return false;
}
void generateBishopPossibleMoves(CBoard *board)
{
    int shift;
    int target;
    u64 move;
    int index = 0;
    u64 magicBB;

    for (int pos = 0; pos < 64; pos++)
    {
        magicBB = 0; // starting position

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                shift = bishopMoves[i][j];
                target = pos + shift;

                // printf("\ntarget = %d", target);
                if (isLegalBishopMove(pos, target) && ((target >= 0) && (target <= 63)))
                {
                    move = (1ULL << target);

                    magicBB |= move;
                }
                else
                    break;
            }
        }
        board->bishopPosAttacks[index] = magicBB;
        index++;
    }
    removeAttackEdges(board);
}

bool isLegalRookMove(int start, int end)
{
    int start_row, start_col, end_row, end_col, dX, dY;
    start_row = floor(start / 8);
    start_col = start % 8;

    end_row = floor(end / 8);
    end_col = end % 8;

    dX = abs(start_col - end_col);
    dY = abs(start_row - end_row);

    if ((dX >= 1 && dY == 0) || (dX == 0 && dY >= 1) || ((dX % 8 == 0) && dY == 0) || (dX == 0 && (dY % 8 == 0)))
        return true;
    else
        return false;
}

int rookMoves[4][7] = {{1, 2, 3, 4, 5, 6, 7}, {-1, -2, -3, -4, -5, -6, -7}, {8, 16, 24, 32, 40, 48, 56}, {-8, -16, -24, -32, -40, -48, -56}};

void generateRookPossibleMoves(CBoard *board)
{
    int shift;
    int target;
    int next_target;
    int index = 0;
    u64 magicBB;
    u64 move;

    for (int position = 0; position < 64; position++)
    {
        magicBB = 0;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                shift = rookMoves[i][j];
                target = position + shift;

                int pos_dir = (shift > 0) ? 1 : -1;
                bool is_row = (abs(shift) < 8) ? true : false;
                int new_shift = shift + ((is_row) ? (pos_dir) : (pos_dir * 8));
                next_target = position + new_shift;

                // printf("\ntarget = %d", target);
                if (isLegalRookMove(position, target) && ((target >= 0) && (target <= 63)))
                {
                    move = (1ULL << target);

                    if (isLegalRookMove(target, next_target) && ((next_target >= 0) && (next_target <= 63)))
                    {
                        magicBB |= move;
                    }
                }
                // end this route
                else
                    break;
            }
        }

        board->rookPosAttacks[index] = magicBB;
        index++;
    }
}

void generatePiecePossibleMoves(CBoard *board)
{
    generateBishopPossibleMoves(board);
    generateRookPossibleMoves(board);
}
