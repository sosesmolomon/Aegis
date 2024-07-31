#ifndef UTILS_H
#define UTILS_H

#include "typedefs.h"
#include "print.h"
#include "init.h"

void identifyPieceType(uint64_t square, Board *board);

int evaluateBoard(Board *board, int** scalarArrays);

int applyScalar(int** scalarArrays, uint64_t piece_bitboard, piece_type type, color color);

int pieceCount(uint64_t board);

uint64_t fullBitBoard(Board* board);

#endif