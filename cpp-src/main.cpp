#include <cmath>
#include <stdio.h>
#include "print.h"
#include "CBoard.h"
#include "init.h"
#include "magic.h"
#include "move.h"
#include "bitboard.h"
// a1 - a8, b1, h1 - h8
//  0 - 7,  8,  56 - 63

void makeQuietMove(enumSquare from, enumSquare to)
{

    /*
    U64 fromBB = C64(1) << move->from;
    U64 toBB = C64(1) << move->to;
    U64 fromToBB = fromBB ^ toBB;     // |+
    pieceBB[move->piece] ^= fromToBB; // update piece bitboard
    pieceBB[move->color] ^= fromToBB; // update white or black color bitboard
    occupiedBB ^= fromToBB;           // update occupied ...
    emptyBB ^= fromToBB;              // ... and empty bitboard
    */
}

int main()
{

    CBoard *b = initCBoard();

    // I don't understand how these magic bitboards work... ignore them for now.
    initMagic(b);

    // printf("knights count = %d\n", count(b->pieceBB[PAWN]&b->coloredBB[WHITE]));



    printBitString(b->wR());

    makeMove(b, a1, a8, ROOK, WHITE);

    printBitString(b->wR());

    printBitString(b->fullBoard());


    return 0;
}
