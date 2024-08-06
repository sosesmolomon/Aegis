#ifndef UTILS_H
#define UTILS_H

#include "typedefs.h"
#include "print.h"
#include "init.h"
#include "move.h"

piece_type identifyPieceType(uint64_t square, Board *board, player_color *color);

bool isInCheck(Board *board, player_color curr_player, possible_move *opponent_moves);

int evaluateBoard(Board *board, int** scalarArrays);

int applyScalar(int** scalarArrays, uint64_t piece_bitboard, piece_type type, player_color color);

int pieceCount(uint64_t board);

void findMoves(Board* board, piece_type curr_piece, player_color curr_player, int position, bool doPrint);

uint64_t fullBitBoard(Board* board);

uint64_t whitePieces(Board *board);

uint64_t blackPieces(Board *board);

#endif