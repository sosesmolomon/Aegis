#include "move.h"
#include "CBoard.h"
#include "bitboard.h"
#include "print.h"
#include "utils.h"
#include "MoveList.h"
#include <cassert>



void genAllLegalMoves(CBoard *b, MoveList *ml) {}

// based on a move_list of legal moves
void makeMove(CBoard *b, moveStruct m)
{
    // printBitString(b->pieceBB[PAWN] & b->coloredBB[WHITE], a2);
    assert((b->pieceBB[m.pT] & (1ULL << m.from)) >= 1 && "Piece mismatch");
    assert((b->coloredBB[m.pC] & (1ULL << m.from)) >= 1 && "Color mismatch");
    assert((b->coloredBB[m.pC] & 1ULL << m.to) == 0 && "Capture same color");


    // is capture?
    if (!isEmptySquare(b, m.to))
    {
        printf("something is here to capture\n");

        // identify piece type, color (obvious), location
        // doCapture() -- turn off old piece, reduce opp count
    }


    // turn off old square
    b->setSq(empty, m.pC, m.from);

    //is capture?


    // turn on new square
    b->setSq(m.pT, m.pC, m.to);

    // b->pieceBB[pieceType].setSq(m.to);
    // b->coloredBB[pieceType].setSq(m.to);

    // setSq(&b->pieceBB[pieceType], to);
    // setSq(&b->coloredBB[color], to);
}