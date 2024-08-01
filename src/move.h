#ifndef MOVE_H
#define MOVE_H
#include "typedefs.h"
#include "print.h"
#include "util.h"
#include "init.h"

bool isEmptySquare(Board* board, int target);

bool pawnOnHomeRow(uint64_t square, player_color *curr_player);

int* findPawnMoves(Board* board, int* possible_moves, uint64_t pawnBB, player_color* curr_player, int position);

void findBishopMoves();

void findKnightMoves();

void findRookMoves();

void findQueenMoves();

void findKingMoves();

#endif