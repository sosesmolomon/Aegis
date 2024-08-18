#ifndef CBOARD_H
#define CBOARD_H

#include <stdint.h>
typedef uint64_t u64;

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
public:
    u64 whitePawns;
    u64 whiteBishops;
    u64 whiteKnights;
    u64 whiteRooks;
    u64 whiteQueens;
    u64 whiteKing;
    u64 blackPawns;
    u64 blackBishops;
    u64 blackKnights;
    u64 blackRooks;
    u64 blackQueens;
    u64 blackKing;
    
    u64 pieceBB[14]; // pointer
    u64 emptyBB;
    u64 occupiedBB;

    u64 *bishopPosAttacks;
    u64 *rookPosAttacks;

    enum enumPiece
    {
        nWhite,
        nBlack,
        nWhitePawn
    };

    u64 fullBoard();
    u64 whitePieces();
    u64 blackPieces();
};

#endif