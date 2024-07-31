#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum piece_type {
    PAWN,
    BISHOP,
    KNIGHT,
    ROOK,
    KING,
    QUEEN
}piece_type;

#define NUM_PIECE_TYPES 6

typedef enum color {
    WHITE,
    BLACK
} color;

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

int pawnScalars[64];
int bishopScalars[64];
int knightScalars[64];
int rooktScalars[64];
int kingScalars[64];
int queenScalars[64];

const char *square_names[64];


#endif