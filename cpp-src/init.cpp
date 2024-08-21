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

    board->white_pawn_home = 0xFFUL << 48;
    board->black_pawn_home = 0xFFUL << 8;

    board->pieceBB[PAWN].getBB() = 0xFFUL << a2 | 0xFFUL << a7;
    board->pieceBB[BISHOP].getBB() = (1ULL << c1) | (1ULL << f1) | (1ULL << c8) | (1ULL << g8);
    board->pieceBB[KNIGHT].getBB() = (1ULL << b1) | (1ULL << g1) | (1ULL << b8) | (1ULL << g8);
    board->pieceBB[ROOK].getBB() = (1ULL << a1) | (1ULL << h1) | (1ULL << a8) | (1ULL << h8);
    board->pieceBB[QUEEN].getBB() = (1ULL << d1) | (1ULL << d8);
    board->pieceBB[KING].getBB() = (1ULL << e1) | (1ULL << e8);

    board->coloredBB[WHITE].getBB() = 0xFFFFUL;
    board->coloredBB[BLACK].getBB() = 0xFFFFUL << a7;

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

////////////////////////////////// PAWN MOVES /////////////////////////////////////////////////////

//should I just find pawn moves each turn? 
//pawns moves are dependent to their current square


////////////////////////////////// BISHOP MOVES /////////////////////////////////////////////////////

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
        board->bishopPosAttacks[pos] = magicBB;
    }
    // remove edges
    for (int i = 0; i < 64; i++)
    {
        board->bishopPosAttacks[i] ^= emptyEdges & board->bishopPosAttacks[i];
    }
}

////////////////////////////////// KNIGHT MOVES /////////////////////////////////////////////////////
int horseMoves[] = {-17, -15, -10, -6, 6, 10, 15, 17};

bool isLegalKnightMove(int start, int end)
{
    int start_row, start_col, end_row, end_col, dX, dY;
    start_row = floor(start / 8);
    start_col = start % 8;

    end_row = floor(end / 8);
    end_col = end % 8;

    dX = abs(start_col - end_col);
    dY = abs(start_row - end_row);

    if ((dX == 1 && dY == 2) ^ (dX == 2 && dY == 1))
        return true;
    else
        return false;
}

void generateKnightPossibleMoves(CBoard *board)
{
    // i know starting position = 47

    // there are 4 legal moves (+6, +15, -10, -17). and 4 illegal moves.
    int shift;
    int target;
    int index = 0;
    u64 magicBB = 0;

    for (int pos = 0; pos < 64; pos++)
    {
        magicBB = 0;

        for (int i = 0; i < 8; i++)
        {
            // -17
            shift = horseMoves[i];

            target = pos + shift;

            if (isLegalKnightMove(pos, target) && isInBounds(target))
            {
                magicBB |= (1ULL << target);
                index++;
            }
        }
        board->knightPosAttacks[pos] = magicBB;
    }
}

////////////////////////////////// ROOK MOVES /////////////////////////////////////////////////////

int rookMoves[4][7] = {{1, 2, 3, 4, 5, 6, 7}, {-1, -2, -3, -4, -5, -6, -7}, {8, 16, 24, 32, 40, 48, 56}, {-8, -16, -24, -32, -40, -48, -56}};

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

                if (isLegalRookMove(position, target) && isInBounds(target))
                {
                    move = (1ULL << target);
                    if (isLegalRookMove(target, next_target) && isInBounds(next_target))
                    {
                        magicBB |= move;
                    }
                }
                // end this route
                else
                    break;
            }
        }
        board->rookPosAttacks[position] = magicBB;
    }
}

////////////////////////////////// QUEEN MOVES /////////////////////////////////////////////////////
void generateQueenPossibleMoves(CBoard *b)
{
    for (int i = 0; i < 64; i++)
    {
        b->queenPosAttacks[i] = b->bishopPosAttacks[i] | b->rookPosAttacks[i];
    }
}

////////////////////////////////// KING MOVES /////////////////////////////////////////////////////

bool isLegalKingMove(int start, int end)
{
    int start_row, start_col, end_row, end_col, dX, dY;
    start_row = floor(start / 8);
    start_col = start % 8;

    end_row = floor(end / 8);
    end_col = end % 8;

    dX = abs(start_col - end_col);
    dY = abs(start_row - end_row);
    if (dX <= 1 && dX >= -1 && dY <= 1 && dY >= -1)
    {
        return true;
    }
    else
    {
        return false;
    }

    // if ((dX >= 1 && dY == 0) || (dX == 0 && dY >= 1) || ((dX % 8 == 0) && dY == 0) || (dX == 0 && (dY % 8 == 0)))
    //     return true;
    // else
    //     return false;
}

int kingMoves[] = {1, -1, 8, -8, 9, -9, 7, -7};
void generateKingPossibleMoves(CBoard *b)
{
    // todo: look for castle opportunity

    int shift, target;
    u64 magicBB, move;
    int index = 0;
    for (int position = 0; position < 64; position++)
    {
        magicBB = 0;

        for (int i = 0; i < 8; i++)
        {
            shift = kingMoves[i];
            target = position + shift;
            move = (1ULL << target);

            if (isLegalKingMove(position, target) && isEmptySquare(b, position) && isInBounds(target))
            {
                magicBB |= move;
            }
        }
        b->kingPosAttacks[position] = magicBB;
    }
}

void generatePiecePossibleMoves(CBoard *board)
{
    //generatePawnPossibleMoves(board); -- pawns work differently...
    generateBishopPossibleMoves(board);
    generateKnightPossibleMoves(board);
    generateRookPossibleMoves(board);
    generateQueenPossibleMoves(board);
    generateKingPossibleMoves(board);
}