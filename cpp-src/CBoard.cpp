#include "CBoard.h"
#include "print.h"
#include "bitboard.h"
#include <stdio.h>

u64 CBoard::fullBoard()
{
    return this->coloredBB[BLACK].b | this->coloredBB[WHITE].b;
}

void CBoard::setSq(int pT, int pC, int sq)
{
    printf("pT = %s, pC = %s\n", pieceToStr[pT], colorToStr[pC]);

    if (pT == empty)
    {
        // turn ON empty in emptyboard
        this->pieceBB[empty].set(sq);

        // turn OFF sq in pieceBB
        // this is a little harder...
        for (int pt = 0; pt <= nPieceT; pt++)
        {
            this->pieceBB[pt].clr(sq);
        }

        // turn OFF sq in colordBB
        this->coloredBB[WHITE].clr(sq);
        this->coloredBB[BLACK].clr(sq);
    }
    else
    {
        this->pieceBB[pT].set(sq);
        this->coloredBB[pC].set(sq);
    }
}

u64 CBoard::wP()
{
    return this->pieceBB[PAWN].b & this->coloredBB[WHITE].b;
}

u64 CBoard::wB()
{
    return this->pieceBB[BISHOP].b & this->coloredBB[WHITE].b;
}

u64 CBoard::wKn()
{
    return this->pieceBB[KNIGHT].b & this->coloredBB[WHITE].b;
}
u64 CBoard::wR()
{
    return this->pieceBB[ROOK].b & this->coloredBB[WHITE].b;
}
u64 CBoard::wQ()
{
    return this->pieceBB[QUEEN].b & this->coloredBB[WHITE].b;
}
u64 CBoard::wK()
{
    return this->pieceBB[KING].b & this->coloredBB[WHITE].b;
}

u64 CBoard::bP()
{
    return this->pieceBB[PAWN].b & this->coloredBB[BLACK].b;
}

u64 CBoard::bB()
{
    return this->pieceBB[BISHOP].b & this->coloredBB[BLACK].b;
}

u64 CBoard::bKn()
{
    return this->pieceBB[KNIGHT].b & this->coloredBB[BLACK].b;
}
u64 CBoard::bR()
{
    return this->pieceBB[ROOK].b & this->coloredBB[BLACK].b;
}
u64 CBoard::bQ()
{
    return this->pieceBB[QUEEN].b & this->coloredBB[BLACK].b;
}
u64 CBoard::bK()
{
    return this->pieceBB[KING].b & this->coloredBB[BLACK].b;
}