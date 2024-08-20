#ifndef BITBOARD_H
#define BITBOARD_H

#include "CBoard.h"

int count(u64 b);

void clearSq(u64 *b, int pos);

void setSq(u64 *b, int pos);

bool test(u64 b, int pos);

#endif