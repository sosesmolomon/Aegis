#include "init.h"
#include "print.h"
#include <stdlib.h>
#include <math.h>

CBoard *initCBoard()
{

    CBoard *board = new CBoard();
    board->bishopPosAttacks = new u64[64];
    board->rookPosAttacks = new u64[64];

    generateMagicBBs(board);

    // for (int i = 0; i < 64; i++)
    // {
    //     lookup_u64[i] = (1ULL << i);
    // }

    return board;
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
void generateBishopMagicBBs(CBoard *board)
{
    int shift;
    int target;
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
                    magicBB |= (1ULL << target);
                }
                else
                    break;
            }
        }
        board->bishopPosAttacks[index] = magicBB;
        index++;
    }
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

void generateRookMagicBBs(CBoard *board)
{
    int shift;
    int target;
    int index = 0;
    u64 magicBB;

    for (int position = 0; position < 64; position++)
    {
        magicBB = 0;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                shift = rookMoves[i][j];
                target = position + shift;

                // printf("\ntarget = %d", target);
                if (isLegalRookMove(position, target) && ((target >= 0) && (target <= 63)))
                {
                    magicBB |= (1ULL << target);
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

u64 emptyEdges = 0b1111111110000001100000011000000110000001100000011000000111111111;

void removeAttackEdges(CBoard *board)
{
    for (int i = 0; i < 64; i++)
    {
        board->rookPosAttacks[i] ^= emptyEdges & board->rookPosAttacks[i];
    }
    for (int i = 0; i < 64; i++)
    {
        board->bishopPosAttacks[i] ^= emptyEdges & board->bishopPosAttacks[i];
    }

}


void generateMagicBBs(CBoard *board)
{
    generateBishopMagicBBs(board);
    generateRookMagicBBs(board);
    removeAttackEdges(board);
}
