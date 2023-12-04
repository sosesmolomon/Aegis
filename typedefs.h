#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <stdint.h>
#include <stdbool.h>

typedef uint64_t Bitboard;

typedef struct
{
    Bitboard pawn_W;
    Bitboard bishop_W;
    Bitboard knight_W;
    Bitboard rook_W;
    Bitboard queen_W;
    Bitboard king_W;

    Bitboard pawn_B;
    Bitboard bishop_B;
    Bitboard knight_B;
    Bitboard rook_B;
    Bitboard queen_B;
    Bitboard king_B;

    int turn;

} Board;

#endif