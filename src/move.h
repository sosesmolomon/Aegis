#ifndef MOVE_H
#define MOVE_H
#include "typedefs.h"
#include "print.h"
#include "util.h"
#include "init.h"
#include "math.h"

bool isEmptySquare(Board* board, int target);

bool pawnOnHomeRow(uint64_t square, player_color *curr_player);

int* findPawnMoves(Board* board, int* possible_moves, uint64_t pawnBB, player_color* curr_player, int position);

int* findBishopMoves(Board *board, int *possible_moves, uint64_t bishopBB, player_color *curr_player, int position);

int* findKnightMoves(Board *board, int *possible_moves, uint64_t knightBB, player_color *curr_player, int position);

void findRookMoves();

void findQueenMoves();

void findKingMoves();

bool isLegalKnightMove(int start, int end);

bool isLegalMove(Board *board, int target, player_color* curr_player);

bool canCapture(Board *board, int target);

#endif