#include "move.h"
#include "CBoard.h"
#include "bitboard.h"
#include "print.h"
#include "utils.h"
#include "MoveList.h"
#include <cassert>

// based on a move_list of legal moves
void makeMove(CBoard *b, moveStruct m, MoveList *game)
{
    // printBitString(b->pieceBB[PAWN] & b->coloredBB[WHITE], a2);
    assert((b->pieceBB[m.pT] & (1ULL << m.from)) >= 1 && "Piece mismatch");
    assert((b->coloredBB[m.pC] & (1ULL << m.from)) >= 1 && "Color mismatch");

    if (!m.isCastlingLong && !m.isCastlingLong)
        assert((b->coloredBB[m.pC] & 1ULL << m.to) == 0 && "Capture same color");
    else
        printf("castling!!!!");
        // need logic here

    // is capture?
    if (m.isCapture)
    {
        int opp_piece_sq = m.to;
        if (m.isEnPassant)
        {
            opp_piece_sq = game->at(game->size() - 1).to;
        }
        // turn off the opposing player's piece
        b->setSq(empty, oppColor(m.pC), opp_piece_sq);
    }

    // move the current player's piece
    b->setSq(empty, m.pC, m.from);
    b->setSq(m.pT, m.pC, m.to);

    // turn off home square for the piece moved. 
    b->pieceHomes ^= (1ULL << m.from);

    game->add(m);
}

// quiet move, no capture...
void undoMove(CBoard *b, moveStruct m, MoveList *game)
{
    b->setSq(m.pT, m.pC, m.from);
    b->setSq(empty, m.pC, m.to);

    // find identify the right move to unmove?
    // game->remove();
}