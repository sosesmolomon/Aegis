#include "CBoard.h"
#include "print.h"
#include "bitboard.h"
#include "utils.h"
#include "magic.h"
#include <stdio.h>
#include <math.h>

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

u64 emptyEdges = 0b1111111110000001100000011000000110000001100000011000000111111111;

void CBoard::initCBoard()
{
    // this->bishopPosAttacks = new u64[64];
    // this->rookPosAttacks = new u64[64];

    this->white_pawn_home = 0xFFUL << 8;
    this->black_pawn_home = 0xFFUL << 48;

    this->pieceBB[PAWN].getBB() = 0xFFUL << a2 | 0xFFUL << a7;
    this->pieceBB[BISHOP].getBB() = (1ULL << c1) | (1ULL << f1) | (1ULL << c8) | (1ULL << g8);
    this->pieceBB[KNIGHT].getBB() = (1ULL << b1) | (1ULL << g1) | (1ULL << b8) | (1ULL << g8);
    this->pieceBB[ROOK].getBB() = (1ULL << a1) | (1ULL << h1) | (1ULL << a8) | (1ULL << h8);
    this->pieceBB[QUEEN].getBB() = (1ULL << d1) | (1ULL << d8);
    this->pieceBB[KING].getBB() = (1ULL << e1) | (1ULL << e8);

    this->coloredBB[WHITE].getBB() = 0xFFFFUL;
    this->coloredBB[BLACK].getBB() = 0xFFFFUL << a7;

    this->pieceBB[empty].getBB() = UINT64_MAX ^ this->fullBoard();

    this->generatePiecePossibleMoves();

    // this->bishop_W = (1ULL << 61) | (1ULL << 58);
    // this->knight_W = (1ULL << 62) | (1ULL << 57);
    // this->rook_W = (1ULL << 63) | (1ULL << 56);
    // this->queen_W = 1ULL << 60;
    // this->king_W = 1ULL << 59;

    // this->pawn_B = 0xFFUL << 8; // takes 0b0000000000000000000000000000000000000000000000000000000011111111 --> 0b0000000000000000000000000000000000000000000000001111111100000000
    // this->bishop_B = (1ULL << 2) | (1ULL << 5);
    // this->knight_B = (1ULL << 1) | (1ULL << 6);
    // this->rook_B = (1ULL << 0) | (1ULL << 7);
    // this->queen_B = 1ULL << 4;
    // this->king_B = 1ULL << 3;
}

////////////////////////////////// PAWN MOVES /////////////////////////////////////////////////////
int pawnMovesW[] = {7, 8, 9, 16};
int pawnMovesB[] = {-7, -8, -9, -16};

void CBoard::generatePawnPossibleMoves()
{
    u64 mask = 0ULL;
    u64 move;

    int shift, target;

    for (int color = BLACK; color <= WHITE; color++)
    {


        for (int sq = a1; sq <= h8; sq++)
        {
            mask = 0ULL;

            for (int i = 0; i < 4; i++)
            {
                shift = (color == WHITE) ? pawnMovesW[i] : pawnMovesB[i];
                target = shift + sq;
                move = (1ULL << target);

                // handle diagonal case
                if (shift == 7 || shift == -7 || shift == 9 || shift == -9)
                {
                    if (isLegalBishopMove(sq, target) && isInBounds(target))
                    {
                        mask |= move;
                    }
                }
                else if (shift == 8 || shift == -8)
                {
                    if (isLegalRookMove(sq, target) && isInBounds(target))
                    {
                        mask |= move;
                    }
                }
                else
                {
                    // shift == 16 or -16
                    if (!pawnOnHome(this, sq, color)) {
                        break;
                    }
                    if (isLegalRookMove(sq, target) && isInBounds(target)) {
                        mask |= move;
                    }
                }
            }
            this->posAttackBBs[PAWN][sq] = mask;
            this->pawnPosAttacks[color][sq] = mask;
        }
    }
}

// should I just find pawn moves each turn?
// pawns moves are dependent to their current square

////////////////////////////////// BISHOP MOVES /////////////////////////////////////////////////////

int bishopMoves[4][7] = {{7, 14, 21, 28, 35, 42, 49}, {-7, -14, -21, -28, -35, -42, -49}, {9, 18, 27, 36, 45, 54, 63}, {-9, -18, -27, -36, -45, -54, -63}};

bool CBoard::isLegalBishopMove(int start, int end)
{
    int start_row, start_col, end_row, end_col, dX, dY;
    start_row = floor(start / 8);
    start_col = start % 8;

    end_row = floor(end / 8);
    end_col = end % 8;

    dX = abs(start_col - end_col);
    dY = abs(start_row - end_row);

    if (dX == dY)
        return true;
    else
        return false;
}

void CBoard::generateBishopPossibleMoves()
{
    int shift;
    int target;
    u64 move;
    int index = 0;
    u64 magicBB;

    for (int pos = 0; pos < 64; pos++)
    {
        magicBB = 0; // starting position

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                shift = bishopMoves[i][j];
                target = pos + shift;

                // printf("\ntarget = %d", target);
                if (isLegalBishopMove(pos, target) && ((target >= 0) && (target <= 63)))
                {
                    move = (1ULL << target);

                    magicBB |= move;
                }
                else
                    break;
            }
        }
        this->posAttackBBs[BISHOP][pos] = magicBB;
        this->bishopPosAttacks[pos] = magicBB;
    }
    // remove edges
    for (int i = 0; i < 64; i++)
    {
        this->posAttackBBs[BISHOP][i] ^= emptyEdges & this->posAttackBBs[BISHOP][i];
        this->bishopPosAttacks[i] ^= emptyEdges & this->bishopPosAttacks[i];
    }
}

////////////////////////////////// KNIGHT MOVES /////////////////////////////////////////////////////
int horseMoves[] = {-17, -15, -10, -6, 6, 10, 15, 17};

bool CBoard::isLegalKnightMove(int start, int end)
{
    int start_row, start_col, end_row, end_col, dX, dY;
    start_row = floor(start / 8);
    start_col = start % 8;

    end_row = floor(end / 8);
    end_col = end % 8;

    dX = abs(start_col - end_col);
    dY = abs(start_row - end_row);

    if ((dX == 1 && dY == 2) ^ (dX == 2 && dY == 1))
        return true;
    else
        return false;
}

void CBoard::generateKnightPossibleMoves()
{
    // i know starting position = 47

    // there are 4 legal moves (+6, +15, -10, -17). and 4 illegal moves.
    int shift;
    int target;
    int index = 0;
    u64 magicBB = 0;

    for (int pos = 0; pos < 64; pos++)
    {
        magicBB = 0;

        for (int i = 0; i < 8; i++)
        {
            // -17
            shift = horseMoves[i];

            target = pos + shift;

            if (isLegalKnightMove(pos, target) && isInBounds(target))
            {
                magicBB |= (1ULL << target);
                index++;
            }
        }
        this->posAttackBBs[KNIGHT][pos] = magicBB;
        this->knightPosAttacks[pos] = magicBB;
    }
}

////////////////////////////////// ROOK MOVES /////////////////////////////////////////////////////

int rookMoves[4][7] = {{1, 2, 3, 4, 5, 6, 7}, {-1, -2, -3, -4, -5, -6, -7}, {8, 16, 24, 32, 40, 48, 56}, {-8, -16, -24, -32, -40, -48, -56}};

bool CBoard::isLegalRookMove(int start, int end)
{
    int start_row, start_col, end_row, end_col, dX, dY;
    start_row = floor(start / 8);
    start_col = start % 8;

    end_row = floor(end / 8);
    end_col = end % 8;

    dX = abs(start_col - end_col);
    dY = abs(start_row - end_row);

    if ((dX >= 1 && dY == 0) || (dX == 0 && dY >= 1) || ((dX % 8 == 0) && dY == 0) || (dX == 0 && (dY % 8 == 0)))
        return true;
    else
        return false;
}

void CBoard::generateRookPossibleMoves()
{
    int shift;
    int target;
    int next_target;
    int index = 0;
    u64 magicBB;
    u64 move;

    for (int position = 0; position < 64; position++)
    {
        magicBB = 0;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                shift = rookMoves[i][j];
                target = position + shift;

                int pos_dir = (shift > 0) ? 1 : -1;
                bool is_row = (abs(shift) < 8) ? true : false;
                int new_shift = shift + ((is_row) ? (pos_dir) : (pos_dir * 8));
                next_target = position + new_shift;

                if (isLegalRookMove(position, target) && isInBounds(target))
                {
                    move = (1ULL << target);
                    if (isLegalRookMove(target, next_target) && isInBounds(next_target))
                    {
                        magicBB |= move;
                    }
                }
                // end this route
                else
                    break;
            }
        }
        this->posAttackBBs[ROOK][position] = magicBB;
        this->rookPosAttacks[position] = magicBB;
    }
}

////////////////////////////////// QUEEN MOVES /////////////////////////////////////////////////////
void CBoard::generateQueenPossibleMoves()
{
    for (int i = 0; i < 64; i++)
    {
        this->posAttackBBs[QUEEN][i] = this->posAttackBBs[BISHOP][i] | this->posAttackBBs[ROOK][i]; 
        this->queenPosAttacks[i] = this->bishopPosAttacks[i] | this->rookPosAttacks[i];
    }
}

////////////////////////////////// KING MOVES /////////////////////////////////////////////////////

bool CBoard::isLegalKingMove(int start, int end)
{
    int start_row, start_col, end_row, end_col, dX, dY;
    start_row = floor(start / 8);
    start_col = start % 8;

    end_row = floor(end / 8);
    end_col = end % 8;

    dX = abs(start_col - end_col);
    dY = abs(start_row - end_row);
    if (dX <= 1 && dX >= -1 && dY <= 1 && dY >= -1)
    {
        return true;
    }
    else
    {
        return false;
    }

    // if ((dX >= 1 && dY == 0) || (dX == 0 && dY >= 1) || ((dX % 8 == 0) && dY == 0) || (dX == 0 && (dY % 8 == 0)))
    //     return true;
    // else
    //     return false;
}

int kingMoves[] = {1, -1, 8, -8, 9, -9, 7, -7};
void CBoard::generateKingPossibleMoves()
{
    // todo: look for castle opportunity

    int shift, target;
    u64 magicBB, move;
    int index = 0;
    for (int position = 0; position < 64; position++)
    {
        magicBB = 0;

        for (int i = 0; i < 8; i++)
        {
            shift = kingMoves[i];
            target = position + shift;
            move = (1ULL << target);

            if (isLegalKingMove(position, target) && isEmptySquare(this, position) && isInBounds(target))
            {
                magicBB |= move;
            }
        }
        this->posAttackBBs[KING][position] = magicBB;
        this->kingPosAttacks[position] = magicBB;
    }
}

void CBoard::generatePiecePossibleMoves()
{
    this->generatePawnPossibleMoves();
    this->generateBishopPossibleMoves();
    this->generateKnightPossibleMoves();
    this->generateRookPossibleMoves();
    this->generateQueenPossibleMoves();
    this->generateKingPossibleMoves();
}

// is this also a MoveList?
void CBoard::genAllLegalMoves(MoveList *ml, int color)
{
    genLegalPawnMoves(ml);
    genLegalBishopMoves(ml, oppColor(color));
    genLegalKnightMoves(ml, oppColor(color));
    genLegalRookMoves(ml, oppColor(color));
    genLegalQueenMoves(ml, oppColor(color));
    genLegalKingMoves(ml, oppColor(color));
}

void CBoard::genLegalPawnMoves(MoveList *ml) {}

void CBoard::genLegalBishopMoves(MoveList *ml, int opp_color)
{

    for (int sq = a1; sq <= h8; sq++)
    {

        printBitString(getBishopAttacks(sq, this->coloredBB[opp_color]), sq);

    }
}

void CBoard::genLegalKnightMoves(MoveList *ml, int opp_color) {}

void CBoard::genLegalRookMoves(MoveList *ml, int opp_color) {}

void CBoard::genLegalQueenMoves(MoveList *ml, int opp_color) {}

void CBoard::genLegalKingMoves(MoveList *ml, int opp_color) {}