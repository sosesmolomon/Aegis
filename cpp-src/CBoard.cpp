#include "MoveList.h"
#include "CBoard.h"
#include "print.h"
#include "bitboard.h"
#include "utils.h"
#include "magic.h"
#include "move.h"
#include "evaluate.h"
#include <stdio.h>
#include <math.h>
#include <string>
#include <regex>
#include <ctype.h>
#include <cassert>
#include <iostream>

u64 CBoard::fullBoard()
{
    return this->coloredBB[BLACK].b | this->coloredBB[WHITE].b;
}

u64 CBoard::emptyBoard()
{
    return (this->fullBoard() ^ UINT64_MAX);
}

void CBoard::setSq(int pT, int pC, int sq)
{
    // printf("pT = %s, pC = %s\n", pieceToStr[pT], colorToStr[pC]);

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

u64 emptyEdges = 0b1111111110000001100000011000000110000001100000011000000111111111;

void CBoard::initCBoard()
{

    this->white_pawn_home = 0xFFUL << 8;
    this->black_pawn_home = 0xFFUL << 48;

    this->player = WHITE;
    this->inCheck[WHITE] = false;
    this->inCheck[BLACK] = false;

    // this->castleRightsShort[WHITE] = true;
    // this->castleRightsShort[BLACK] = true;

    // this->castleRightsLong[WHITE] = true;
    // this->castleRightsLong[BLACK] = true;

#ifdef TEST

    this->pieceBB[BISHOP].getBB() |= 1ULL << c3;
    this->coloredBB[BLACK].getBB() |= 1ULL << c3;

    this->pieceBB[QUEEN].getBB() |= 1ULL << g7;
    this->coloredBB[BLACK].getBB() |= 1ULL << g7;

    this->pieceBB[KNIGHT].getBB() |= 1ULL << f5;
    this->coloredBB[BLACK].getBB() |= 1ULL << f5;

    this->pieceBB[ROOK].getBB() |= 1ULL << a8;
    this->coloredBB[BLACK].getBB() |= 1ULL << a8;

    this->pieceBB[PAWN].getBB() |= 1ULL << a1;
    this->coloredBB[BLACK].getBB() |= 1ULL << a1;

    this->pieceBB[PAWN].getBB() |= 1ULL << h2;
    this->coloredBB[BLACK].getBB() |= 1ULL << h2;

#elif EP
    // must make move (d7/f7 to d5/f5) first.
    this->pieceBB[PAWN].getBB() |= 0xFFUL << a7;
    this->coloredBB[BLACK].getBB() |= 0xFFUL << a7;

    this->pieceBB[PAWN].getBB() |= 1ULL << e5;
    this->coloredBB[WHITE].getBB() |= 1ULL << e5;

#elif CASTL_W
    this->player = WHITE;
    this->pieceBB[ROOK].getBB() |= (1ULL << 0) | (1ULL << 7);
    this->coloredBB[WHITE].getBB() |= (1ULL << 0) | (1ULL << 7);
    this->pieceBB[KING].getBB() |= (1ULL << 4);
    this->coloredBB[WHITE].getBB() |= (1ULL << 4);

#elif CASTL_B
    this->player = BLACK;
    this->pieceBB[ROOK].getBB() |= (1ULL << a8) | (1ULL << h8);
    this->coloredBB[BLACK].getBB() |= (1ULL << a8) | (1ULL << h8);
    this->pieceBB[KING].getBB() |= (1ULL << e8);
    this->coloredBB[BLACK].getBB() |= (1ULL << e8);

    // this->pieceBB[ROOK].getBB() |= (1ULL << d1);
    // this->coloredBB[WHITE].getBB() |= (1ULL << d1);
    this->pieceBB[KNIGHT].getBB() |= (1ULL << g6);
    this->coloredBB[WHITE].getBB() |= (1ULL << g6);

#elif UNDO
    // capture and undo setup
    this->pieceBB[KNIGHT].getBB() |= (1ULL << d4);
    this->coloredBB[WHITE].getBB() |= (1ULL << d4);

    this->pieceBB[BISHOP].getBB() |= (1ULL << h5);
    this->coloredBB[WHITE].getBB() |= (1ULL << h5);

    this->pieceBB[KNIGHT].getBB() |= (1ULL << g4);
    this->coloredBB[WHITE].getBB() |= (1ULL << g4);

    this->pieceBB[QUEEN].getBB() |= (1ULL << e8);
    this->coloredBB[WHITE].getBB() |= (1ULL << e8);

    this->pieceBB[BISHOP].getBB() |= (1ULL << c2) | (1ULL << b3);
    this->coloredBB[BLACK].getBB() |= (1ULL << c2) | (1ULL << b3);

    this->pieceBB[KING].getBB() |= (1ULL << b1) | (1ULL << e2);
    this->coloredBB[WHITE].getBB() |= (1ULL << b1);
    this->coloredBB[BLACK].getBB() |= (1ULL << e2);

#elif EXITCHECK
    // possible moves to exit check
    this->pieceBB[KING].getBB() |= (1ULL << g3);
    this->coloredBB[WHITE].getBB() |= (1ULL << g3);

    this->pieceBB[BISHOP].getBB() |= (1ULL << f1);
    this->coloredBB[WHITE].getBB() |= (1ULL << f1);

    this->pieceBB[PAWN].getBB() |= (1ULL << f4);
    this->coloredBB[WHITE].getBB() |= (1ULL << f4);

    this->pieceBB[KING].getBB() |= (1ULL << a8);
    this->coloredBB[BLACK].getBB() |= (1ULL << a8);

    this->pieceBB[QUEEN].getBB() |= (1ULL << h3);
    this->coloredBB[BLACK].getBB() |= (1ULL << h3);

    this->pieceBB[KNIGHT].getBB() |= (1ULL << g4);
    this->coloredBB[BLACK].getBB() |= (1ULL << g4);

    this->pieceBB[ROOK].getBB() |= (1ULL << h8);
    this->coloredBB[BLACK].getBB() |= (1ULL << h8);

    this->pieceBB[QUEEN].getBB() |= (1ULL << a1);
    this->coloredBB[BLACK].getBB() |= (1ULL << a1);

    this->pieceBB[QUEEN].getBB() |= (1ULL << a7);
    this->coloredBB[BLACK].getBB() |= (1ULL << a7);

    this->pieceBB[QUEEN].getBB() |= (1ULL << h7);
    this->coloredBB[BLACK].getBB() |= (1ULL << h7);

    this->pieceBB[QUEEN].getBB() |= (1ULL << h6);
    this->coloredBB[BLACK].getBB() |= (1ULL << h6);

#elif CHECKMATE
    this->castleRightsShort[WHITE] = false;
    this->castleRightsShort[BLACK] = false;

    this->castleRightsLong[WHITE] = false;
    this->castleRightsLong[BLACK] = false;

    this->inCheck[WHITE] = true;

    this->pieceBB[KING].getBB() |= (1ULL << e4);
    this->coloredBB[WHITE].getBB() |= (1ULL << e4);

    this->pieceBB[ROOK].getBB() |= (1ULL << a1) | (1ULL << h8) | (1ULL << a2);
    this->coloredBB[WHITE].getBB() |= (1ULL << a1) | (1ULL << h8) | (1ULL << a2);

    // this->pieceBB[PAWN].getBB() |= (1ULL << c5);
    // this->coloredBB[WHITE].getBB() |= (1ULL << c5);

    this->pieceBB[QUEEN].getBB() |= (1ULL << a5);
    this->coloredBB[BLACK].getBB() |= (1ULL << a5);

    this->pieceBB[ROOK].getBB() |= (1ULL << d8) | (1ULL << d1) | (1ULL << f8) | (1ULL << h5) | (1ULL << c3);
    this->coloredBB[BLACK].getBB() |= (1ULL << d8) | (1ULL << d1) | (1ULL << f8) | (1ULL << h5) | (1ULL << c3);

    this->pieceBB[PAWN].getBB() |= (1ULL << d7);
    this->coloredBB[BLACK].getBB() |= (1ULL << d7);

    this->pieceBB[KING].getBB() |= (1ULL << h1);
    this->coloredBB[BLACK].getBB() |= (1ULL << h1);

#else
    this->pieceBB[PAWN].getBB() = 0xFFUL << a2 | 0xFFUL << a7;
    this->pieceBB[BISHOP].getBB() = (1ULL << c1) | (1ULL << f1) | (1ULL << c8) | (1ULL << f8);
    this->pieceBB[KNIGHT].getBB() = (1ULL << b1) | (1ULL << g1) | (1ULL << b8) | (1ULL << g8);
    this->pieceBB[ROOK].getBB() = (1ULL << a1) | (1ULL << h1) | (1ULL << a8) | (1ULL << h8);
    this->pieceBB[QUEEN].getBB() = (1ULL << d1) | (1ULL << d8);
    this->pieceBB[KING].getBB() = (1ULL << e1) | (1ULL << e8);

    this->coloredBB[BLACK].getBB() = 0xFFFFUL << a7;
    this->coloredBB[WHITE].getBB() = 0xFFFFUL;

#endif

    this->generatePiecePossibleMoves();
}

void CBoard::clearBoard() {
    
    for (int i = 0; i < 7; i++) {
        this->pieceBB[i].getBB() = 0ULL;
    }
    this->coloredBB[WHITE].getBB() = 0ULL;
}

void CBoard::initTestBoard()
{

    // --------------------------------------------------------------------------------

    this->pieceBB[empty].getBB() = UINT64_MAX ^ this->fullBoard();

    printBitString(this->fullBoard());
    printBitString(this->coloredBB[BLACK]);
    printBitString(this->pieceBB[KING]);

    this->generatePiecePossibleMoves();
}

////////////////////////////////// PAWN MOVES /////////////////////////////////////////////////////
int pawnMovesW[] = {7, 8, 9, 16};
int pawnMovesB[] = {-7, -8, -9, -16};

void CBoard::generatePawnPossibleMoves()
{
    u64 a_mask = 0ULL;
    u64 p_mask = 0ULL;
    u64 move;

    int shift, target;

    for (int color = BLACK; color <= WHITE; color++)
    {

        for (int sq = a1; sq <= h8; sq++)
        {
            a_mask = 0ULL;
            p_mask = 0ULL;

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
                        a_mask |= move;
                    }
                }
                else if (shift == 8 || shift == -8)
                {
                    if (isLegalRookMove(sq, target) && isInBounds(target))
                    {
                        p_mask |= move;
                    }
                }
                else
                {
                    // shift == 16 or -16
                    if (!pawnOnHome(this, sq, color))
                    {
                        break;
                    }
                    if (isLegalRookMove(sq, target) && isInBounds(target))
                    {
                        p_mask |= move;
                    }
                }
            }
            // this->posAttackBBs[PAWN][sq] = mask;
            this->pawnPosPushes[color][sq] = p_mask;
            this->pawnPosAttacks[color][sq] = a_mask;
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

            if (isLegalKingMove(position, target) && isInBounds(target))
            {
                magicBB |= move;
            }
        }
        this->posAttackBBs[KING][position] = magicBB;
        this->kingPosAttacks[position] = magicBB;
    }
}

// generates a bitboard of moves for each piece type on every square of the board
void CBoard::generatePiecePossibleMoves()
{
    this->white_pawn_home = 0xFFUL << 8;
    this->black_pawn_home = 0xFFUL << 48;
    this->generatePawnPossibleMoves();
    this->generateBishopPossibleMoves();
    this->generateKnightPossibleMoves();
    this->generateRookPossibleMoves();
    this->generateQueenPossibleMoves();
    this->generateKingPossibleMoves();
}

/*
void CBoard::genAllLegalMoves(MoveList *ml, MoveList *game_ml, int color, bool onlyAttacks)
{

    this->legalAttackedSquares[color].getBB() = 0ULL;
    int opp_color = oppColor(color);

    // do these need the game? -- only PAWN -- for enPassantCheck
    genLegalPawnMoves(ml, game_ml, opp_color, onlyAttacks);
    genLegalBishopMoves(ml, game_ml, opp_color, onlyAttacks);
    genLegalKnightMoves(ml, game_ml, opp_color, onlyAttacks);
    genLegalRookMoves(ml, game_ml, opp_color, onlyAttacks);
    genLegalQueenMoves(ml, game_ml, opp_color, onlyAttacks);
    genLegalKingMoves(ml, game_ml, opp_color, onlyAttacks);
}

void CBoard::genLegalPawnMoves(MoveList *ml, MoveList *game_ml, int opp_color, bool onlyAttacks)
{
    int player_color = oppColor(opp_color);
    u64 pawns = (this->pieceBB[PAWN] & this->coloredBB[player_color]);
    int sq, target;
    int i, j;
    int count = countBits(pawns);
    int count_attacks;
    int jump;

    for (i = 0; i < count; i++)
    {
        if (!pawns)
        {
            printf("breaking... no pawns?\n");
            break;
        }

        sq = firstOne(pawns);
        u64 attacks = this->pawnPosAttacks[player_color][sq];
        count_attacks = countBits(attacks);

        for (j = 0; j < count_attacks; j++)
        {
            if (!attacks)
            {
                printf("breaking... no pawn attacks?\n");
                break;
            }
            target = firstOne(attacks);

            // capture...
            if (isLegalBishopMove(sq, target))
            {
                this->legalAttackedSquares[player_color].getBB() |= (1ULL << target); // still want to track potentially attacking diagonally
                // printf("checking captures at %s\n", sqToStr[target]);
                if (isEmptySquare(this, target) && canEnPassant(game_ml, sq, target, player_color))
                {
                    if (!onlyAttacks)
                        ml->add(moveStruct(sq, target, PAWN, player_color, true, true, false, false, PAWN));
                }

                if (isOpposingPiece(this, sq, target, opp_color))
                {
                    if (!onlyAttacks)
                        ml->add(moveStruct(sq, target, PAWN, player_color, true, false, false, false, identifyPieceType(this, target)));
                }
            }

            // SINGLE pawn push
            else if ((abs(target - sq) != 16) && isLegalRookMove(sq, target) && isEmptySquare(this, target))
            {
                if (!onlyAttacks)
                    ml->add(moveStruct(sq, target, PAWN, player_color));
            }
            // DOUBLE pawn push
            else
            {
                jump = (player_color == WHITE) ? target - 8 : target + 8;
                // printf("while looking at PAWN double push to %s, must check %s to be empty\n", sqToStr[target], sqToStr[jump]);
                if (isLegalRookMove(sq, target) && isEmptySquare(this, target) && isEmptySquare(this, jump))
                {
                    if (!onlyAttacks)
                        ml->add(moveStruct(sq, target, PAWN, player_color));
                }
            }
            attacks ^= (1ULL << target);
        }
        // turn off the square
        pawns ^= (1ULL << sq);
    }
}

/**
 * 1. iterates through the bishops on the board for 1 color
 * 2. gets the attacks from magic bb
 * 3. walks through each of these attacked squares: populates a moveStruct (from, to, pT, pC, isCapture, etc.)
 * 4. adds the moveStruct to a MoveList
 *
 * ALSO
 * populates legalAttackedSquares at the same time.

void CBoard::genLegalBishopMoves(MoveList *ml, MoveList *game_ml, int opp_color, bool onlyAttacks)
{
    int player_color = oppColor(opp_color);
    u64 bishops = (this->pieceBB[BISHOP] & this->coloredBB[player_color]);
    int sq, target;
    int i, j;
    int count = countBits(bishops);
    int count_attacks;

    for (i = 0; i < count; i++)
    {
        if (!bishops)
        {
            printf("breaking... no bishops?\n");
            break;
        }

        sq = firstOne(bishops);

        // magic bb to get bishop attacks
        u64 attacks = getBishopAttacks(sq, this->fullBoard());
        count_attacks = countBits(attacks);

        for (j = 0; j < count_attacks; j++)
        {
            if (!attacks)
            {
                printf("breaking... no bishop attacks?\n");
                break;
            }
            target = firstOne(attacks);
            // printf("%s on %s to %s is%slegal\n", pieceToStr[BISHOP], sqToStr[sq], sqToStr[target], (canCapture(this, sq, target, BISHOP, BLACK)) ? " " : " NOT ");

            // you can always move to an empty square
            if (isEmptySquare(this, target))
            {
                this->legalAttackedSquares[player_color].getBB() |= (1ULL << target);
                if (!onlyAttacks)
                    ml->add(moveStruct(sq, target, BISHOP, player_color));
            }
            else
            {
                if (noFriendlyFire(this, sq, target, player_color))
                {
                    this->legalAttackedSquares[player_color].getBB() |= (1ULL << target);
                    if (!onlyAttacks)
                        ml->add(moveStruct(sq, target, BISHOP, player_color, true, false, false, false, identifyPieceType(this, target)));
                }
            }
            attacks ^= (1ULL << target);
        }
        // turn off the square
        bishops ^= (1ULL << sq);
    }
}

void CBoard::genLegalKnightMoves(MoveList *ml, MoveList *game_ml, int opp_color, bool onlyAttacks)
{
    int player_color = oppColor(opp_color);
    u64 knights = (this->pieceBB[KNIGHT] & this->coloredBB[player_color]);
    int sq, target;
    int i, j;
    int count = countBits(knights);
    int count_attacks;

    for (i = 0; i < count; i++)
    {
        if (!knights)
        {
            printf("breaking... no knights?\n");
            break;
        }

        sq = firstOne(knights);
        u64 attacks = this->knightPosAttacks[sq];
        count_attacks = countBits(attacks);

        for (j = 0; j < count_attacks; j++)
        {
            if (!attacks)
            {
                printf("breaking... no knight attacks?\n");
                break;
            }
            target = firstOne(attacks);
            // printf("%s on %s to %s is%slegal\n", pieceToStr[KNIGHT], sqToStr[sq], sqToStr[target], (canCapture(this, sq, target, KNIGHT, BLACK)) ? " " : " NOT ");
            if (isEmptySquare(this, target))
            {
                this->legalAttackedSquares[player_color].getBB() |= (1ULL << target);
                if (!onlyAttacks)
                    ml->add(moveStruct(sq, target, KNIGHT, player_color));
            }
            else
            {
                // printf("%s knight attack %s to %s? \n", colorToStr[player_color], sqToStr[sq], sqToStr[target]);
                if (noFriendlyFire(this, sq, target, player_color))
                {
                    // printf("legal attack on %s\n", sqToStr[target]);
                    this->legalAttackedSquares[player_color].getBB() |= (1ULL << target);
                    if (!onlyAttacks)
                        ml->add(moveStruct(sq, target, KNIGHT, player_color, true, false, false, false, identifyPieceType(this, target)));
                }
            }
            attacks ^= (1ULL << target);
        }
        // turn off the square
        knights ^= (1ULL << sq);
    }
}

void CBoard::genLegalRookMoves(MoveList *ml, MoveList *game_ml, int opp_color, bool onlyAttacks)
{
    int player_color = oppColor(opp_color);
    u64 rooks = (this->pieceBB[ROOK] & this->coloredBB[player_color]);
    int sq, target;
    int i, j;
    int count = countBits(rooks);
    int count_attacks;

    for (i = 0; i < count; i++)
    {
        if (!rooks)
        {
            printf("breaking... no rooks?\n");
            break;
        }

        sq = firstOne(rooks);
        u64 attacks = getRookAttacks(sq, this->fullBoard());
        count_attacks = countBits(attacks);

        // process attacks --------------(u64 attacks, int count_attacks, sq, pT, pC)------no return: helper does ml->add(move)----------------------------
        for (j = 0; j < count_attacks; j++)
        {
            if (!attacks)
            {
                printf("breaking... no rook attacks?\n");
                break;
            }
            target = firstOne(attacks);
            // printf("%s on %s to %s is%slegal\n", pieceToStr[ROOK], sqToStr[sq], sqToStr[target], (canCapture(this, sq, target, ROOK, BLACK)) ? " " : " NOT ");
            if (isEmptySquare(this, target))
            {
                this->legalAttackedSquares[player_color].getBB() |= (1ULL << target);
                if (!onlyAttacks)
                    ml->add(moveStruct(sq, target, ROOK, player_color));
            }
            else
            {
                if (noFriendlyFire(this, sq, target, player_color))
                {
                    this->legalAttackedSquares[player_color].getBB() |= (1ULL << target);
                    if (!onlyAttacks)
                        ml->add(moveStruct(sq, target, ROOK, player_color, true, false, false, false, identifyPieceType(this, target)));
                }
            }
            attacks ^= (1ULL << target);
        }
        // turn off the square
        rooks ^= (1ULL << sq);
        // end process attacks ----------------------------------------------------
    }
}

void CBoard::genLegalQueenMoves(MoveList *ml, MoveList *game_ml, int opp_color, bool onlyAttacks)
{
    int player_color = oppColor(opp_color);
    u64 queens = (this->pieceBB[QUEEN] & this->coloredBB[player_color]);
    int sq, target;
    int i, j;
    int count = countBits(queens);
    int count_attacks;

    for (i = 0; i < count; i++)
    {
        if (!queens)
        {
            printf("breaking... no queens?\n");
            break;
        }

        sq = firstOne(queens);
        u64 attacks = getBishopAttacks(sq, this->fullBoard()) | getRookAttacks(sq, this->fullBoard());
        count_attacks = countBits(attacks);

        for (j = 0; j < count_attacks; j++)
        {
            if (!attacks)
            {
                printf("breaking... no queen attacks?\n");
                break;
            }
            target = firstOne(attacks);

            if (sq == f5 && (target == e4 || target == f4 || target == g4))
            {
                printf("okay... what is going on? anything at %s: %d\n", sqToStr[target], int(isEmptySquare(this, target)));
            }

            // printf("%s on %s to %s is%slegal\n", pieceToStr[QUEEN], sqToStr[sq], sqToStr[target], (canCapture(this, sq, target, QUEEN, BLACK)) ? " " : " NOT ");
            if (isEmptySquare(this, target))
            {
                this->legalAttackedSquares[player_color].getBB() |= (1ULL << target);
                if (!onlyAttacks)
                    ml->add(moveStruct(sq, target, QUEEN, player_color));
            }
            else
            {
                if (noFriendlyFire(this, sq, target, player_color))
                {
                    this->legalAttackedSquares[player_color].getBB() |= (1ULL << target);
                    if (!onlyAttacks)
                        ml->add(moveStruct(sq, target, QUEEN, player_color, true, false, false, false, identifyPieceType(this, target)));
                }
            }
            attacks ^= (1ULL << target);
        }
        // turn off the square
        queens ^= (1ULL << sq);
    }
}

void CBoard::genLegalKingMoves(MoveList *ml, MoveList *game_ml, int opp_color, bool onlyAttacks)
{
    int player_color = oppColor(opp_color);
    u64 king = (this->pieceBB[KING] & this->coloredBB[player_color]);
    int sq, target;
    int i, j;
    int count = countBits(king); // should be 1
    if (count != 1)
    {
        // printBitString(this->pieceBB[KING]);
        // printBitString(this->coloredBB[player_color]);
        printf("someting weird. more or less than 1 %s king... got: %d\n", colorToStr[player_color], count);
    }
    int count_attacks;

    ;
    for (i = 0; i < count; i++)
    {
        if (!king)
        {
            printf("breaking... no kings?\n");
            break;
        }

        sq = firstOne(king);

        if (!onlyAttacks)
        {
            if (canCastleShort(sq, player_color))
            {
                ml->add(moveStruct(sq, 0, KING, player_color, 0, 0, 1, 0));
            }

            if (canCastleLong(sq, player_color))
            {
                ml->add(moveStruct(sq, 0, KING, player_color, 0, 0, 0, 1));
            }
        }

        // printf("the king on %s can%s castle: %s %s\n", sqToStr[sq], (canCastleShort(sq, player_color) || canCastleLong(sq, player_color)) ? "" : " NOT", (canCastleShort(sq, player_color)) ? "SHORT" : "", (canCastleLong(sq, player_color)) ? "LONG" : "");

        // how to find castling options?
        u64 attacks = this->kingPosAttacks[sq];
        // printBitString(attacks, sq);
        count_attacks = countBits(attacks);

        for (j = 0; j < count_attacks; j++)
        {
            if (!attacks)
            {
                printf("breaking... no king attacks?\n");
                break;
            }
            target = firstOne(attacks);
            // printf("%s on %s to %s is%slegal\n", pieceToStr[KING], sqToStr[sq], sqToStr[target], (canCapture(this, sq, target, KING, BLACK)) ? " " : " NOT ");
            if (isEmptySquare(this, target))
            {
                this->legalAttackedSquares[player_color].getBB() |= (1ULL << target);
                if (!onlyAttacks)
                    ml->add(moveStruct(sq, target, KING, player_color));
            }
            else
            {
                if (noFriendlyFire(this, sq, target, player_color))
                {
                    this->legalAttackedSquares[player_color].getBB() |= (1ULL << target);
                    if (!onlyAttacks)
                        ml->add(moveStruct(sq, target, KING, player_color, true, false, false, false, identifyPieceType(this, target)));
                }
            }
            attacks ^= (1ULL << target);
        }
        // turn off the square
        king ^= (1ULL << sq);
    }
}

*/

void CBoard::updateCastlingRights(const moveStruct& m) {
    if (m.pT == KING) {
        if (m.pC == WHITE) {
            // say current rights = 1111 &= ~(0001 | 0010) -> ~(0011) --> (1100) 
            this->currentCastlingRights &= ~(WHITE_SHORT | WHITE_LONG);
        } else {
            this->currentCastlingRights &= ~(BLACK_SHORT | BLACK_LONG);
        }
    }

    if (m.pT == ROOK || m.capturedP == ROOK) {
        // if capturing h1, or moving from h1
        if (m.from == h1 || m.to == h1) {
            this->currentCastlingRights &= ~(WHITE_SHORT);
        }
        if (m.from == a1 || m.to == a1) {
            this->currentCastlingRights &= ~(WHITE_LONG);
        }
        if (m.from == h8 || m.to == h8) {
            this->currentCastlingRights &= ~(BLACK_SHORT);
        }
        if (m.from == a8 || m.to == a8) {
            this->currentCastlingRights &= ~(BLACK_LONG);
        }
    }
}

bool CBoard::canCastleShort(int sq, int color)
{
    // castleRightsShort[white] == white retains the right to castle kingside

    // instead of this = search the move list to ensure king and close rook haven't moved. 
    // searching the move list would probably be a lot faster if each move was a u64... bc you would just do a mask
    bool hasCastleRights = (color == WHITE) ? this->currentCastlingRights & WHITE_SHORT : this->currentCastlingRights & BLACK_SHORT;

    bool pathIsClear;
    // also need to make sure we're not in check currently
    bool pathIsSafe;

    if (color)
    {
        pathIsClear = isEmptySquare(this, f1) && isEmptySquare(this, g1);
        pathIsSafe = !this->isAttacked(f1, color ^ WHITE) && !this->isAttacked(g1, color ^ WHITE);
    }
    else
    {
        pathIsClear = isEmptySquare(this, f8) && isEmptySquare(this, g8);
        pathIsSafe = !this->isAttacked(f8, color ^ WHITE) && !this->isAttacked(g8, color ^ WHITE);
    }
    return hasCastleRights && pathIsSafe && pathIsClear;
}

bool CBoard::canCastleLong(int sq, int color)
{
    int rookSq = (color) ? a1 : a8;
    bool hasCastleRights = (color == WHITE) ? this->currentCastlingRights & WHITE_LONG : this->currentCastlingRights & BLACK_LONG;
    bool pathIsSafe;
    bool pathIsClear;
    if (color)
    {
        pathIsClear = isEmptySquare(this, b1) && isEmptySquare(this, c1) && isEmptySquare(this, d1);
        pathIsSafe =  !this->isAttacked(c1, color ^ WHITE) && !this->isAttacked(d1, color ^ WHITE);
    }
    else
    {
        pathIsClear = isEmptySquare(this, b8) && isEmptySquare(this, c8) && isEmptySquare(this, d8);
        pathIsSafe = !this->isAttacked(c8, color ^ WHITE) && !this->isAttacked(d8, color ^ WHITE);
    }
    return hasCastleRights && pathIsSafe && pathIsClear;
}

// b->legalAttackedSquares[color] is updated by b->
bool CBoard::isInCheck(int color)
{
    // what squares is the opponent looking at?
    // this->legalAttackedSquares[(color^WHITE)];

    u64 kBB = this->pieceBB[KING] & this->coloredBB[color];
    int k_sq = firstOne(kBB);

    return isAttacked(k_sq, color ^ WHITE);
}

bool CBoard::isInCheckmate(MoveList *legals, int color)
{
    if (legals->size() == 0 && this->isInCheck(color))
    {
        return true;
    }
    return false;
}

bool CBoard::isInStalemate(MoveList *legals, int color)
{
    if (legals->size() == 0 && !this->isInCheck(color))
    {
        return true;
    }
    return false;
}

void CBoard::verifyLegalMoves(MoveList *ml, MoveList *game, MoveList *verified)
{
    bool isLegal;
    moveStruct m;

    // black attacks before the move
    for (int i = 0; i < ml->size(); i++)
    {
        m = ml->at(i);

        makeMove(this, m, game);

        if (!this->isInCheck(this->player))
        {
            verified->add(m);
        }

        undoMove(this, m, game);
    }
}

void CBoard::loadFEN(const std::string &fen, MoveList *game)
{
    // clear the board first?

    bool loadingBoard = true;
    int curr;
    curr = a8;

    char c;
    int color;

    std::string sub;

    int rows[8] = {a8, a7, a6, a5, a4, a3, a2, a1};
    int swap[8] = {a7, a6, a5, a4, a3, a2, a1, 0};
    int row_counter = 0;

    for (int i = 0; i < fen.length(); i++)
    {

        c = fen.at(i);

        if (loadingBoard)
        {
            // should be at h8, g8, f8, e8, etc.    -15 puts you at the start of the next row
            if (c == '/')
            {
                assert(row_counter != 7 && "More than 7 \'s");
                curr = swap[row_counter];
                row_counter++;
            }

            // we have this amount of whitespace...
            if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8')
            {
                switch (c)
                {
                case '1':
                    curr += 1;
                    break;
                case '2':
                    curr += 2;
                    break;
                case '3':
                    curr += 3;
                    break;
                case '4':
                    curr += 4;
                    break;
                case '5':
                    curr += 5;
                    break;
                case '6':
                    curr += 6;
                    break;
                case '7':
                    curr += 7;
                    break;
                case '8':
                    curr += 8;
                    break;
                default:
                    break;
                }
            }
            else
            {

                if (isupper(c))
                {
                    color = WHITE;
                }
                else
                {
                    color = BLACK;
                }

                switch (c)
                {
                case 'p':
                case 'P':
                    // printf("allocating %s PAWN at %s\n", colorToStr[color], sqToStr[curr]);
                    this->pieceBB[PAWN].getBB() |= 1ULL << curr;
                    this->coloredBB[color].getBB() |= 1ULL << curr;
                    curr += 1;
                    break;

                case 'b':
                case 'B':
                    // printf("allocating %s BISHOP at %s\n", colorToStr[color], sqToStr[curr]);
                    this->pieceBB[BISHOP].getBB() |= 1ULL << curr;
                    this->coloredBB[color].getBB() |= 1ULL << curr;
                    curr += 1;
                    break;

                case 'n':
                case 'N':
                    // printf("allocating %s KNIGHT at %s\n", colorToStr[color], sqToStr[curr]);
                    this->pieceBB[KNIGHT].getBB() |= 1ULL << curr;
                    this->coloredBB[color].getBB() |= 1ULL << curr;
                    curr += 1;
                    break;

                case 'r':
                case 'R':
                    // printf("allocating %s ROOK at %s\n", colorToStr[color], sqToStr[curr]);
                    this->pieceBB[ROOK].getBB() |= 1ULL << curr;
                    this->coloredBB[color].getBB() |= 1ULL << curr;
                    curr += 1;
                    break;

                case 'q':
                case 'Q':
                    // printf("allocating %s QUEEN at %s\n", colorToStr[color], sqToStr[curr]);
                    this->pieceBB[QUEEN].getBB() |= 1ULL << curr;
                    this->coloredBB[color].getBB() |= 1ULL << curr;
                    curr += 1;
                    break;

                case 'k':
                case 'K':
                    // printf("allocating %s KING at %s\n", colorToStr[color], sqToStr[curr]);
                    this->pieceBB[KING].getBB() |= 1ULL << curr;
                    this->coloredBB[color].getBB() |= 1ULL << curr;
                    curr += 1;
                    break;

                case ' ':
                    loadingBoard = false;
                    break;

                default:
                    break;
                }
            }
        }
        else
        {

            sub = fen.substr(i);

            // Regex to match one or more whitespace characters
            std::regex ws_re("\\s+");
            std::vector<std::string> words(
                std::sregex_token_iterator(sub.begin(), sub.end(), ws_re, -1),
                std::sregex_token_iterator());

            // ** current player **
            this->player = (words.at(0) == "w") ? WHITE : BLACK;

            std::string &castling = words.at(1);

            
            uint8_t white_short = (castling.find('K') != std::string::npos) ? 1 << 0 : 0 << 0;
            uint8_t white_long = (castling.find('k') != std::string::npos) ? 1 << 1 : 0 << 1;
            uint8_t black_short = (castling.find('Q') != std::string::npos) ? 1 << 2 : 0 << 2;
            uint8_t black_long = (castling.find('q') != std::string::npos) ? 1 << 3 : 0 << 2;

            this->currentCastlingRights = white_short | white_long | black_short | black_long;

            // ** en passant **.... maybe we can add game_moves last move as the pawn double push
            // could also change how I track en passant. whenever you move double, you say OPP_COLOR-can-EP = target_square (where moved)
            std::string &en_passant = words.at(2);

            // printf("en passant = %d", en_passant.compare("-"));

            if (!(en_passant.compare("-") == 0))
            {

                int to = (this->player == WHITE) ? squareEnumFromStr(en_passant) - 8 : squareEnumFromStr(en_passant) + 8;
                int fr = (this->player == WHITE) ? to + 16 : to - 16; // if its WHITE turn, then black moved pawn twice, go up in rows, sq+8

                assert(game->size() == 0 && "move list is not 0");
                game->add(moveStruct(fr, to, PAWN, this->player ^ WHITE, 0, 1));
                assert(game->size() == 1 && "move list is not 1 after adding move");
            }

            // Halfmove clock: The number of halfmoves since the last capture or pawn advance, used for the fifty-move rule.[9]
            std::string &half_moves = words.at(3);

            // Fullmove number: The number of the full moves. It starts at 1 and is incremented after Black's move.
            std::string &full_moves = words.at(4);

            // printf("player to move = %s\n", colorToStr[this->player]);
            // printf("castling info = %s\n", castling.c_str());
            // printf("en passant info = %s\n", en_passant.c_str());
            // printf("half moves info = %s\n", half_moves.c_str());
            // printf("full moves info = %s\n", full_moves.c_str());

            // Need to verify:
            // isInCheck[WHITE], isInCheck[BLACK]
            // is

            return;
        }
    }
}

u64 CBoard::perft(int depth, MoveList *game, PerftResults &results)
{
    if (depth == 0)
    {
        results.nodes += 1;
        return 1ULL;
    }

    MoveList all;   // Stack allocation
    MoveList legal; // Stack allocation
    this->genAllMoves(&all, game);
    this->verifyLegalMoves(&all, game, &legal);

    // printf("there are %d moves\n", legal.size());

    int n_moves;
    int i;
    u64 nodes = 0;

    for (i = 0; i < legal.size(); i++)
    {
        moveStruct move = legal.at(i);

        makeMove(this, move, game);

        this->player ^= WHITE;


        // if (move.from == b1 && move.to == a3) {
        //     printf("LOOK HERE: ");
        // }

        collectPerftStats(move, results, game);

        nodes += perft(depth - 1, game, results);

    
        // Output move and nodes
        this->player ^= WHITE;
        undoMove(this, move, game);
    }

    return nodes;
}

u64 CBoard::perftDivide(int depth, MoveList *game, PerftResults &results)
{
    u64 nodes = 0;
    printBoard(this, this->fullBoard());

    MoveList all;   // Stack allocation
    MoveList legal; // Stack allocation
    this->genAllMoves(&all, game);
    this->verifyLegalMoves(&all, game, &legal);
    
    printf("moves at depth 1 = %d\n", (int)legal.size());

    for (int i = 0; i < legal.size(); i++)
    {
        moveStruct move = legal.at(i);

        // Make the move
        makeMove(this, move, game);

        // Switch player
        this->player ^= WHITE;


        // Recurse
        uint64_t childNodes = this->perft(depth - 1, game, results);
        nodes += childNodes;


        // Output move and nodes
        move.toString();
        printf(": %llu\n", childNodes);
        // std::cout << move.toString() << ": " << childNodes << std::endl;

        // Switch player back
        this->player ^= WHITE;

        // Undo the move
        undoMove(this, move, game);
    }
    std::cout << "Total nodes at depth " << depth << ": " << nodes << std::endl;
    return nodes;
}

void CBoard::collectPerftStats(moveStruct &move, PerftResults &results, MoveList *game)
{
    if (move.isCapture)
    {
        results.captures += 1;

        if (move.isEnPassant)
        {
            results.enPassantCaptures += 1;
        }
    }

    if (move.isCastlingShort || move.isCastlingLong)
    {
        results.castles += 1;
    }

    if (move.isPromotion)
    {
        results.promotions += 1;
    }

    MoveList all;
    MoveList legal;
    this->genAllMoves(&all, game);
    this->verifyLegalMoves(&all, game, &legal);

    if (this->isInCheck(this->player))
    {
        results.checks += 1;
        if (this->isInCheckmate(game, this->player))
        {
            results.checkmates += 1;
        }
    }
}