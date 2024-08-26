#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include "CBoard.h"


bool pawnOnHome(CBoard *b, int sq, int color);
bool isEmptySquare(CBoard* b, int square);
bool isInBounds(int square);
bool singleBit(u64 b, int sq);
int countBits(u64 b);

// isAttacked(square)
// identifyPiece(square)


#endif