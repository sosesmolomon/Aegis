#include "utils.h"
#include "print.h"

#include "CBoard.h"

bool squareIsAttacked(CBoard *b, int sq, int color)
{
    int opp_color = oppColor(color);
    // need more here.
    // this is for checks.
    return true;
}

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

int oppColor(int color)
{
    return color ^= WHITE;
}

int firstOne(u64 b)
{
    // shift n times until there is a 1
    int n = 0;

    if (b)
    {
        while ((b & 1) == 0)
        {
            n++;
            b >>= 1;
        }
    }

    // clears the bottom bits somehow?
    // b = (b >> u64(n+1)) << u64(n+1);

    return n;
}

int lastOne(u64 b) {
    int n = 63;
    u64 max = (1ULL<<h8);

    if (b) {
        while ((b & max) == 0) {
            n--;
            b<<=1;
        }
    }

    return n;
}

bool canCapture(CBoard *b, int start, int target, int pT, int opp_color) {
    //  make sure:
    // not moving to same color square
    if ((b->coloredBB[oppColor(opp_color)] & (1ULL << target)) >= 1)
    {
        return false;
    }


    // not entering check
    // anything else? 
    return true;
}