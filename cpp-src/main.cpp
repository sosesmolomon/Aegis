#include <cmath>
#include <stdio.h>
#include "print.h"
#include "CBoard.h"
#include "init.h"
#include "magic.h"
#include "move.h"
#include "bitboard.h"
#include "MoveList.h"
#include "utils.h"
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

    printf("single bit == %d\n", singleBit(b->pieceBB[KNIGHT].getBB(), a3));
    printf("single bit == %d\n", singleBit(b->pieceBB[KNIGHT].getBB(), b1));
    // return 0;

    // printBitString(b->knightPosAttacks[a4], a4);
    // genAllLegalMoves(b, &ml);

    // ml.print();

    ml.add(moveStruct(a1, a5, ROOK, WHITE));
    // ml.add(moveStruct(h1, c4, QUEEN, BLACK));
    // ml.add(moveStruct(a8, a2, ROOK, BLACK));
    makeMove(b, ml.at(0));
    // makeMove(b, ml.at(1));
    // makeMove(b, ml.at(2));


    b->pieceBB[empty].getBB() = UINT64_MAX ^ b->fullBoard();


    for (int i=0; i<nPieceT+1;i++) {
        printf("Current state for %s:\n", pieceToStr[i]);
        printBitString(b->pieceBB[i].getBB());
    }
    printf("Current state for %s:\n", colorToStr[0]);
    printBitString(b->coloredBB[0]);
    printf("Current state for %s:\n", colorToStr[1]);
    printBitString(b->coloredBB[1]);
    return 0;


    ml.print(); 
    return 0;
    ml.remove(2);
    ml.print();


    // I don't understand how these magic bitboards work... ignore them for now.
    initMagic(b);





    return 0;
}
