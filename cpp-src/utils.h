#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include "CBoard.h"

bool isEmptySquare(CBoard* b, int square);
bool isInBounds(int square);
bool singleBit(u64 b, int sq);

// isAttacked(square)
// identifyPiece(square)


#endif