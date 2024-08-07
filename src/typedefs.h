#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum piece_type
{
    NONE,
    PAWN,
    BISHOP,
    KNIGHT,
    ROOK,
    KING,
    QUEEN,
} piece_type;



#define NUM_PIECE_TYPES 6

typedef enum player_color
{
    WHITE,
    BLACK
} player_color;

typedef struct Board
{
    uint64_t pawn_W;
    uint64_t bishop_W;
    uint64_t knight_W;
    uint64_t rook_W;
    uint64_t queen_W;
    uint64_t king_W;

    uint64_t pawn_B;
    uint64_t bishop_B;
    uint64_t knight_B;
    uint64_t rook_B;
    uint64_t queen_B;
    uint64_t king_B;

    int turn;

} Board;

typedef struct possible_move
{
    player_color color;
    int start;
    int shift;
    piece_type piece;
    float eval_after_move;
} possible_move;

int *pawn_moves;
int *bishop_moves;
int *knight_moves;
int *rook_moves;
int *queen_moves;
int *king_moves;

int pawnScalars[64];
int bishopScalars[64];
int knightScalars[64];
int rooktScalars[64];
int kingScalars[64];
int queenScalars[64];

const char square_names[64][3];

uint64_t white_pawn_home;
uint64_t black_pawn_home;

#endif