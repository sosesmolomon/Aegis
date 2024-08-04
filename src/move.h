#ifndef MOVE_H
#define MOVE_H
#include "typedefs.h"
#include "print.h"
#include "util.h"
#include "init.h"
#include "math.h"

bool isEmptySquare(Board* board, int target);

bool pawnOnHomeRow(player_color *curr_player, int position);

int* findPawnMoves(Board* board, int* possible_moves, player_color* curr_player, int position);

int* findBishopMoves(Board *board, int *possible_moves, player_color *curr_player, int position);

int* findKnightMoves(Board *board, int *possible_moves, player_color *curr_player, int position);

int* findRookMoves(Board *board, int *possible_moves, player_color *curr_player, int position);

int* findQueenMoves(Board* board, int *possible_moves, player_color *curr_player, int position);

int* findKingMoves(Board* board, int *possible_moves, player_color *curr_player, int position);

bool isLegalBishopMove(int start, int end);

bool isLegalKnightMove(int start, int end);

bool isLegalRookMove(int start, int end);

bool isLegalMove(Board *board, int target, player_color* curr_player);


#endif