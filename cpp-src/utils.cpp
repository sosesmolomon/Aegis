#include "utils.h"
#include "print.h"

#include "CBoard.h"

bool pawnOnHome(CBoard *b, int sq, int color)
{
    u64 square = (1ULL << sq);
    // printf("color = %s\n", colorToStr[color]);

    // printf("check = %d", int(square & b->white_pawn_home));
    if (color)
        return ((square & b->white_pawn_home) >= 1);
    else
        return ((square & b->black_pawn_home) >= 1);
}

bool singleBit(u64 b, int sq)
{
    b &= (1ULL << sq);
    return b >= 1;
}

bool isEmptySquare(CBoard *b, int square)
{
    u64 mask = 1ULL << square;
    return ((mask & b->fullBoard()) >= 1) ? 0 : 1;
}

bool isInBounds(int square)
{
    if (square >= 64 | square < 0)
        return false;
    return true;
};

int countBits(u64 b)
{
    int r = 0;

    while (b)
    {
        b &= b - 1;
        r++;
    }
    return r;
}