#include "utils.h"

#include "CBoard.h"

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
