#include <cmath>
#include <stdio.h>
#include "print.h"
#include "CBoard.h"
#include "init.h"
#include "magic.h"
// a1 - a8, b1, h1 - h8
//  0 - 7,  8,  56 - 63

void makeQuietMove()
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

    CBoard *board = initCBoard();
    initMagic(board);


    printBitString(board->bishopPosAttacks[h2]);

    getAttacks(board->)


    // for (int i = 0; i < 64; i++)
    // {
    //     printf("%d:\n", i);
    //     printBitString(board->rookMagicBBs[i]);
    // }

    return 0;
}
