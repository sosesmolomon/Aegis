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

    if (m.isCastlingLong || m.isCastlingLong)
    {
        if (m.isCastlingShort)
        {
            // white
            if (m.pC)
            {
                b->setSq(empty, WHITE, e1);
                b->setSq(empty, WHITE, h1);

                b->setSq(KING, WHITE, g1);
                b->setSq(ROOK, WHITE, f1);
            }
            // black
            else
            {
                b->setSq(empty, WHITE, e8);
                b->setSq(empty, WHITE, h8);

                b->setSq(KING, WHITE, g8);
                b->setSq(ROOK, WHITE, f8);
            }
        }
        else
        {
            // white
            if (m.pC)
            {
                b->setSq(empty, WHITE, e1);
                b->setSq(empty, WHITE, a1);

                b->setSq(KING, WHITE, c1);
                b->setSq(ROOK, WHITE, d1);
            }
            // black
            else
            {
                b->setSq(empty, WHITE, e8);
                b->setSq(empty, WHITE, a8);

                b->setSq(KING, WHITE, c8);
                b->setSq(ROOK, WHITE, d8);
            }
        }
    }
    else
    {
        assert((b->coloredBB[m.pC] & 1ULL << m.to) == 0 && "Capture same color");

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
    }
    game->add(m);
}

// quiet move, no capture...
void undoMove(CBoard *b, moveStruct m, MoveList *game)
{
    if (m.isCastlingLong || m.isCastlingLong)
    {
        if (m.isCastlingShort)
        {
            // white
            if (m.pC)
            {
                b->setSq(KING, WHITE, e1);
                b->setSq(ROOK, WHITE, h1);

                b->setSq(empty, WHITE, g1);
                b->setSq(empty, WHITE, f1);
            }
            // black
            else
            {
                b->setSq(KING, WHITE, e8);
                b->setSq(ROOK, WHITE, h8);

                b->setSq(empty, WHITE, g8);
                b->setSq(empty, WHITE, f8);
            }
        }
        else
        {
            // white
            if (m.pC)
            {
                b->setSq(KING, WHITE, e1);
                b->setSq(ROOK, WHITE, a1);

                b->setSq(empty, WHITE, c1);
                b->setSq(empty, WHITE, d1);
            }
            // black
            else
            {
                b->setSq(KING, WHITE, e8);
                b->setSq(ROOK, WHITE, a8);

                b->setSq(empty, WHITE, c8);
                b->setSq(empty, WHITE, d8);
            }
        }
    }
    else
    {
        assert((b->coloredBB[m.pC] & 1ULL << m.to) == 0 && "Capture same color");

        // is capture?
        if (m.isCapture)
        {
            int opp_piece_sq = m.to;
            if (m.isEnPassant)
            {
                opp_piece_sq = game->at(game->size() - 1).to;
            }
            // turn the pawn back on before en passant capture
            b->setSq(PAWN, oppColor(m.pC), opp_piece_sq);

        }

        b->setSq(m.pT, m.pC, m.from);
        b->setSq(empty, m.pC, m.to);
    }
    // find identify the right move to unmove?
    game->remove(game->size()-1); // remove just the end of the list?
}