#include "move.h"
#include "CBoard.h"
#include "bitboard.h"
#include "print.h"
#include "utils.h"
#include "MoveList.h"
#include <cassert>



// based on a move_list of legal moves
void makeMove(CBoard *b, moveStruct m)
{
    // printBitString(b->pieceBB[PAWN] & b->coloredBB[WHITE], a2);
    assert((b->pieceBB[m.pT] & (1ULL << m.from)) >= 1 && "Piece mismatch");
    assert((b->coloredBB[m.pC] & (1ULL << m.from)) >= 1 && "Color mismatch");
    assert((b->coloredBB[m.pC] & 1ULL << m.to) == 0 && "Capture same color");

    // is capture?
    if (m.isCapture)
    {
        // assert opposite color & move >= 1
        // assert same color & move == 0

        
        // identify piece type, color (obvious), location
        // doCapture() -- turn off old piece, reduce opp count
    }

    b->setSq(empty, m.pC, m.from);
    b->setSq(m.pT, m.pC, m.to);
}

// quiet move, no capture...
void undoMove(CBoard *b, moveStruct m)
{
    b->setSq(m.pT, m.pC, m.from);
    b->setSq(empty, m.pC, m.to);
}