#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include "CBoard.h"

int getFile(int sq);
int getRow(int sq);
bool squareIsAttacked(CBoard *b, int sq, int color);
bool pawnOnHome(CBoard *b, int sq, int color);
bool isEmptySquare(CBoard* b, int square);
bool isInBounds(int square);
bool singleBit(u64 b, int sq);
int countBits(u64 b);
int oppColor(int color);
// isAttacked(square)
// identifyPiece(square)
int firstOne(u64 b);
int lastOne(u64 b);
bool isOpposingPiece(CBoard *b, int start, int target, int opp_color);
bool noFriendlyFire(CBoard *b, int start, int target, int player_color);
bool canEnPassant(MoveList *game, int sq, int target, int player_color);

#endif