#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include "CBoard.h"


bool squareIsAttacked(CBoard *b, int sq, int color);
bool pawnOnHome(CBoard *b, int sq, int color);
bool isEmptySquare(CBoard* b, int square);
bool isInBounds(int square);
bool singleBit(u64 b, int sq);
int countBits(u64 b);
int oppColor(int color);
// isAttacked(square)
// identifyPiece(square)


#endif