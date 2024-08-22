#ifndef CBOARD_H
#define CBOARD_H


#include <stdint.h>
#include "bitboard.h"
typedef uint64_t u64;

const int nPieceT = 6;
const int nPieceC = 12;  


// a1 = 0
// h8 = 63
enum enumSquare
{
    a1,
    b1,
    c1,
    d1,
    e1,
    f1,
    g1,
    h1,
    a2,
    b2,
    c2,
    d2,
    e2,
    f2,
    g2,
    h2,
    a3,
    b3,
    c3,
    d3,
    e3,
    f3,
    g3,
    h3,
    a4,
    b4,
    c4,
    d4,
    e4,
    f4,
    g4,
    h4,
    a5,
    b5,
    c5,
    d5,
    e5,
    f5,
    g5,
    h5,
    a6,
    b6,
    c6,
    d6,
    e6,
    f6,
    g6,
    h6,
    a7,
    b7,
    c7,
    d7,
    e7,
    f7,
    g7,
    h7,
    a8,
    b8,
    c8,
    d8,
    e8,
    f8,
    g8,
    h8
};

// u64 *lookup_u64;

class CBoard
{
public: // problem with this is I need to call each of these individually. It would be better if I could call BB[WHITE + KNIGHT] -- BB [1+3]

    Bitboard pieceBB[nPieceT+1]; //empty board
    Bitboard coloredBB[2];

    u64 white_pawn_home;
    u64 black_pawn_home;


    // maybe these are only needed as u64?

    u64 pawnPosAttacks[2][64];
    u64 bishopPosAttacks[64];
    u64 knightPosAttacks[64];
    u64 rookPosAttacks[64];
    u64 queenPosAttacks[64];
    u64 kingPosAttacks[64];


    u64 fullBoard();

    u64 wP();
    u64 wB();
    u64 wKn();
    u64 wR();
    u64 wQ();
    u64 wK();

    u64 bP();
    u64 bB();
    u64 bKn();
    u64 bR();
    u64 bQ();
    u64 bK();

    void setSq(int pT, int pC, int sq);
};

enum pieceT {
    PAWN, // 0
    BISHOP, // 1
    KNIGHT, // 2
    ROOK,
    QUEEN,
    KING, // 5
    empty
};

// black = 0
// white = 1
enum pieceC {
    BLACK,
    WHITE
};


#endif