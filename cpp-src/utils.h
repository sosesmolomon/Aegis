#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include "CBoard.h"


int oppColor(int color);

int getFile(int sq);
int getRow(int sq);

bool isInBounds(int square);

bool singleBit(u64 b, int sq);
int countBits(u64 b);

int firstOne(u64 b);
int lastOne(u64 b);

bool canEnPassant(MoveList *game, int sq, int target, int player_color);


bool squareIsAttacked(CBoard *b, int sq, int color);
bool pawnOnHome(CBoard *b, int sq, int color);
bool isEmptySquare(CBoard* b, int square);
int identifyPieceType(CBoard *b, int sq, u64 bitboard);
int identifyPieceColor(CBoard *b, int sq);
bool isOpposingPiece(CBoard *b, int start, int target, int opp_color);
bool noFriendlyFire(CBoard *b, int start, int target, int player_color);


#endif