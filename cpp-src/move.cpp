#include "move.h"
#include "CBoard.h"
#include "bitboard.h"
#include "print.h"
#include "utils.h"
#include <cassert>

// based on a move_list of legal moves
void makeMove(CBoard *b, int from, int to, int pieceType, color color)
{
    assert((b->pieceBB[pieceType] & (1ULL << from)) == 1 && "Piece mismatch");
    assert((b->coloredBB[color] & (1ULL << from)) == 1 && "Color mismatch");
    assert((b->coloredBB[color] & 1ULL << to) == 0 && "Capture same color");

    // turn off old square
    clearSq(&b->pieceBB[pieceType], from);
    clearSq(&b->coloredBB[color], from);

    // is capture?
    if (!isEmptySquare(b, to))
    {
        printf("something is here to capture\n");

        // identify piece type, color (obvious), location
        // doCapture() -- turn off old piece, reduce opp count
    }

    // turn on new square
    setSq(&b->pieceBB[pieceType], to);
    setSq(&b->coloredBB[color], to);
}