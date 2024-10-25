#include "CBoard.h"
#include "utils.h"
#include "print.h"
#include "magic.h"
#include "MoveList.h"

void CBoard::genAllMoves(MoveList *ml, MoveList *game)
{
    int color = this->player;
    u64 attacked = 0ULL;
    u64 targetBB = this->coloredBB[color] ^ UINT64_MAX; // removes the need for friendlyFire check


    this->genPawnMoves(ml, game, targetBB, color);
    this->genBishopMoves(ml, targetBB, color);
    this->genKnightMoves(ml, targetBB, color);
    this->genRookMoves(ml, targetBB, color);
    this->genQueenMoves(ml, targetBB, color);
    this->genKingMoves(ml, game, targetBB, color);
}

void CBoard::genQuietMoves(MoveList *ml, MoveList *game, int color)
{
    // this->genAllMoves(ml, game, (this->coloredBB[color] ^ this->fullBoard()));
}
void CBoard::genCaptureMoves(MoveList *ml, MoveList *game, int color)
{
    // this->genAllMoves(ml, game, (this->coloredBB[color] & this->fullBoard()));
}

// fills pieceAttacks[color][piece]
void CBoard::fillAttackBBs(MoveList *game, u64 targetBB, int color)
{
    // captures
    // u64 targetBB = this->fullBoard() & this->coloredBB[this->player^WHITE];

    // all moves
    // u64 targetBB = UINT64_MAX;

    // quiet moves
    // u64 targetBB = ( UINT64_MAX ^ this->fullBoard() );

    this->genPawnAttacks(game, targetBB, color);
    this->genBishopAttacks(targetBB, color);
    this->genKnightAttacks(targetBB, color);
    this->genRookAttacks(targetBB, color);
    this->genQueenAttacks(targetBB, color);
    this->genKingAttacks(targetBB, color);
}

void CBoard::genPawnMoves(MoveList *ml, MoveList *game, u64 targetBB, int color)
{
    u64 allBB = this->pieceBB[PAWN] & this->coloredBB[color];
    u64 toBB;

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        this->genPawnPushes(ml, color, fr);
        this->genPawnDiags(ml, game, color, fr);
        this->genPawnPromotions(ml, color, fr);
    }
}

void CBoard::genPawnPushes(MoveList *ml, int color, int fr)
{

    // exclude all pieces, and the last row (not handling promotions here)
    u64 end_row = (color == WHITE) ? (0xFFULL << a8) : 0xFFULL;
    u64 toBB = this->pawnPosPushes[color][fr] & this->emptyBoard() & (UINT64_MAX ^ end_row);

    for (int to = firstOne(toBB); to != 64; to = firstOne(toBB))
    {
        // double jump remover... probably slow?
        if (abs(to - fr) == 16 && !isEmptySquare(this, (color == WHITE) ? to-8 : to + 8)) 
        {
            continue;
        }
        ml->add(moveStruct(fr, to, PAWN, color));
    }
}

void CBoard::genPawnDiags(MoveList *ml, MoveList *game, int color, int fr)
{

    u64 toBB = this->pawnPosAttacks[color][fr];

    for (int to = firstOne(toBB); to != 64; to = firstOne(toBB))
    {
        // TODO: replace canEnPassant() with a simple check to the CBoard...
        if (isEmptySquare(this, to) && canEnPassant(game, fr, to, color))
        {
            int pT = identifyPieceType(this, to);
            ml->add(moveStruct(fr, to, PAWN, color, 1, 1, 0, 0, pT));
        }
        else
        {
            if (((1ULL << to) & this->coloredBB[color ^ WHITE]) != 0)
            {
                int pT = identifyPieceType(this, to);
                ml->add(moveStruct(fr, to, PAWN, color, 1, 0, 0, 0, pT));
            }
        }
    }
}

void CBoard::genPawnPromotions(MoveList *ml, int color, int fr)
{
    u64 end_row = (color == WHITE) ? (0xFFULL << a8) : 0xFFULL;
    u64 toBB = this->pawnPosPushes[color][fr] & this->emptyBoard() & end_row;
    for (int to = firstOne(toBB); to != 64; to = firstOne(toBB))
    {
        ml->add(moveStruct(fr, to, PAWN, color, 0, 0, 0, 0, 0, 1)); // NEED ML FOR PROMOTIONS (default queening)
    }
}

void CBoard::genPawnAttacks(MoveList *game, u64 targetBB, int color)
{

    u64 allBB = this->pieceBB[PAWN] & this->coloredBB[color];

    u64 toBB = 0ULL;

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        toBB |= this->pawnPosAttacks[color][fr] & targetBB;
    }

    this->pieceAttacks[color][PAWN] = toBB;
}

void CBoard::genBishopMoves(MoveList *ml, u64 targetBB, int color)
{
    u64 allBB = this->pieceBB[BISHOP] & this->coloredBB[color];
    u64 toBB;

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        toBB = getBishopAttacks(fr, this->fullBoard()) & targetBB;
        for (int to = firstOne(toBB); to != 64; to = firstOne(toBB))
        {

            if (isEmptySquare(this, to))
            {
                ml->add(moveStruct(fr, to, BISHOP, color));
            }
            else
            {
                int pT = identifyPieceType(this, to);
                ml->add(moveStruct(fr, to, BISHOP, color, 1, 0, 0, 0, pT));
            }
        }
    }
}
void CBoard::genBishopAttacks(u64 targetBB, int color)
{

    u64 allBB = this->pieceBB[BISHOP] & this->coloredBB[color];

    u64 toBB = 0ULL;

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        toBB |= (getBishopAttacks(fr, this->fullBoard()) & targetBB);
    }
    this->pieceAttacks[color][BISHOP] = toBB;
}

// generate quiet moves, captures, all moves, based on targetBB;
void CBoard::genKnightMoves(MoveList *ml, u64 targetBB, int color)
{

    u64 allBB = this->pieceBB[KNIGHT] & this->coloredBB[color];
    u64 toBB;

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        toBB = this->knightPosAttacks[fr] & targetBB;
        for (int to = firstOne(toBB); to != 64; to = firstOne(toBB))
        {

            if (isEmptySquare(this, to))
            {
                ml->add(moveStruct(fr, to, KNIGHT, color));
            }
            else
            {
                int pT = identifyPieceType(this, to);
                ml->add(moveStruct(fr, to, KNIGHT, color, 1, 0, 0, 0, pT));
            }
        }
    }
}

// use this as new move generation -- pass emptyBB or opp_colorBB for moves/attacks
void CBoard::genKnightAttacks(u64 targetBB, int color)
{
    u64 allBB = this->pieceBB[KNIGHT] & this->coloredBB[color];
    u64 toBB = 0ULL;

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        toBB |= this->knightPosAttacks[fr] & targetBB;
    }
    this->pieceAttacks[color][KNIGHT] = toBB;
}

void CBoard::genRookMoves(MoveList *ml, u64 targetBB, int color)
{
    u64 allBB = this->pieceBB[ROOK] & this->coloredBB[color];
    u64 toBB;

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        toBB = getRookAttacks(fr, this->fullBoard()) & targetBB;
        for (int to = firstOne(toBB); to != 64; to = firstOne(toBB))
        {
            if (isEmptySquare(this, to))
            {
                ml->add(moveStruct(fr, to, ROOK, color));
            }
            else
            {
                int pT = identifyPieceType(this, to);
                ml->add(moveStruct(fr, to, ROOK, color, 1, 0, 0, 0, pT));
            }
        }
    }
}

void CBoard::genRookAttacks(u64 targetBB, int color)
{

    u64 allBB = this->pieceBB[ROOK] & this->coloredBB[color];
    u64 toBB = 0ULL;

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        toBB |= (getRookAttacks(fr, this->fullBoard()) & targetBB);
    }
    this->pieceAttacks[color][ROOK] = toBB;
}

void CBoard::genQueenMoves(MoveList *ml, u64 targetBB, int color)
{
    u64 allBB = this->pieceBB[QUEEN] & this->coloredBB[color];
    u64 toBB;

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        toBB = (getBishopAttacks(fr, this->fullBoard()) | getRookAttacks(fr, this->fullBoard())) & targetBB;
        for (int to = firstOne(toBB); to != 64; to = firstOne(toBB))
        {

            if (isEmptySquare(this, to))
            {
                ml->add(moveStruct(fr, to, QUEEN, color));
            }
            else
            {
                int pT = identifyPieceType(this, to);
                ml->add(moveStruct(fr, to, QUEEN, color, 1, 0, 0, 0, pT));
            }
        }
    }
}

void CBoard::genQueenAttacks(u64 targetBB, int color)
{
    u64 allBB = this->pieceBB[QUEEN] & this->coloredBB[color];
    u64 toBB = 0ULL;

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        toBB |= (getRookAttacks(fr, this->fullBoard()) & targetBB);
        toBB |= (getBishopAttacks(fr, this->fullBoard()) & targetBB);
    }
    this->pieceAttacks[color][QUEEN] = toBB;
}

void CBoard::genKingMoves(MoveList *ml, MoveList *game, u64 targetBB, int color)
{
    u64 allBB = this->pieceBB[KING] & this->coloredBB[color];
    u64 toBB;
    int sq;

    // this->fillAttackBBs(game, UINT64_MAX, color ^ WHITE);

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        if (canCastleShort(fr, color))
        {
            sq = (color) ? g1 : g8;
            ml->add(moveStruct(fr, sq, KING, color, 0, 0, 1, 0));
        }

        if (canCastleLong(fr, color))
        {
            sq = (color) ? c1 : c8;
            ml->add(moveStruct(fr, sq, KING, color, 0, 0, 0, 1));
        }

        toBB = this->kingPosAttacks[fr] & targetBB;
        for (int to = firstOne(toBB); to != 64; to = firstOne(toBB))
        {
            if (isEmptySquare(this, to))
            {
                ml->add(moveStruct(fr, to, KING, color));
            }
            else
            {
                int pT = identifyPieceType(this, to);
                ml->add(moveStruct(fr, to, KING, color, 1, 0, 0, 0, pT));
            }
        }
    }
}

void CBoard::genKingAttacks(u64 targetBB, int color)
{
    u64 allBB = this->pieceBB[KING] & this->coloredBB[color];
    u64 toBB = 0ULL;

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        toBB |= this->kingPosAttacks[fr] & targetBB;
    }
    this->pieceAttacks[color][KING] = toBB;
}

// is (color) attacking square (to)?
// add castling looking flag
bool CBoard::isAttacked(int to, int color)
{
    // printf("checking if the square %s is attacked by %s\n", sqToStr[to], colorToStr[color]);
    // pawn attacking square

    // in order to check backwards, you need to flip the color for pawn attacks
    if ((this->pawnPosAttacks[color^WHITE][to] & this->pieceBB[PAWN] & this->coloredBB[color]) != 0)
    {
        return true;
    }

    if ((this->knightPosAttacks[to] & this->pieceBB[KNIGHT] & this->coloredBB[color]) != 0)
    {
        return true;
    }
    if ((getBishopAttacks(to, this->fullBoard()) & (this->pieceBB[BISHOP] | this->pieceBB[QUEEN]) & this->coloredBB[color]) != 0)
    {
        return true;
    }

    // printBitString(getRookAttacks(to, this->fullBoard()) & (this->pieceBB[ROOK] | this->pieceBB[QUEEN]) & this->coloredBB[color]);
    if ((getRookAttacks(to, this->fullBoard()) & (this->pieceBB[ROOK] | this->pieceBB[QUEEN]) & this->coloredBB[color]) != 0)
    {
        return true;
    }

    if ((this->kingPosAttacks[to] & this->pieceBB[KING] & this->coloredBB[color]) != 0)
    {
        return true;
    }
    return false;
}
// is (sq) defended by (color)
bool CBoard::isDefended(int sq, int color) {
    return this->isAttacked(sq, color);
}
