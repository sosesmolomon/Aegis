#include <cmath>
#include <stdio.h>
#include "print.h"
#include "CBoard.h"
#include "init.h"
#include "magic.h"
#include "move.h"
#include "bitboard.h"
#include "MoveList.h"
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
    MoveList ml = MoveList();


    printBitString(b->knightPosAttacks[a4], a4);
    genAllLegalMoves(b, &ml);

    ml.print();

    ml.add(moveStruct(a1, a8, ROOK, WHITE));
    ml.add(moveStruct(h1, c4, QUEEN, WHITE));
    ml.add(moveStruct(a8, a2, ROOK, BLACK));
    ml.print(); 
    return 0;
    ml.remove(2);
    ml.print();


    // I don't understand how these magic bitboards work... ignore them for now.
    initMagic(b);





    return 0;
}
