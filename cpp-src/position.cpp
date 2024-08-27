#include "position.h"
#include "utils.h"
#include "magic.h"

// all of these should be CBoard functions?

// is this also a MoveList?
void genAllLegalMoves(CBoard *b, MoveList *ml, int color)
{
    genLegalPawnMoves(b);
    genLegalBishopMoves(b, oppColor(color));
    genLegalKnightMoves(b, oppColor(color));
    genLegalRookMoves(b, oppColor(color));
    genLegalQueenMoves(b, oppColor(color));
    genLegalKingMoves(b, oppColor(color));
}

void genLegalPawnMoves(CBoard *b) {}

void genLegalBishopMoves(CBoard *b, int opp_color)
{

    for (int sq = a1; sq <= h8; sq++)
    {
        getBishopAttacks(sq, b->coloredBB[opp_color]);

    }
}

void genLegalKnightMoves(CBoard *b, int opp_color) {}

void genLegalRookMoves(CBoard *b, int opp_color) {}

void genLegalQueenMoves(CBoard *b, int opp_color) {}

void genLegalKingMoves(CBoard *b, int opp_color) {}