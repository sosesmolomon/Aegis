#include <cmath>
#include <stdio.h>
#include "print.h"
#include "CBoard.h"
#include "init.h"
#include "magic.h"
#include "move.h"
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


    printBitString(b->bishopPosAttacks[h2]);


    printf("PAWN = %d, BISHOP = %d, KING = %d\n", PAWN, BISHOP, KING);
    printf("WHITE = %d, BLACK = %d\n", WHITE, BLACK);
    printf("pieceBB[WHITE_KNIGHT] == pieceBB[%d]\n", (WHITE + KNIGHT));

    // printBitString(b->whitePawns);


    printBitString(b->pieceBB[PAWN]);

    printBitString(b->coloredBB[WHITE]);
    printBitString(b->coloredBB[BLACK] & b->pieceBB[KNIGHT]); // specific piece_type bitboard
    printBitString(b->coloredBB[BLACK]);


    printBitString(b->wB());

    // for (int i = 0; i < 64; i++)
    // {
    //     printf("%d:\n", i);
    //     printBitString(board->rookMagicBBs[i]);
    // }

    return 0;
}
