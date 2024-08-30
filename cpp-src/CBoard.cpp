#include "CBoard.h"
#include "MoveList.h"
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
    this->pieceBB[BISHOP].getBB() = (1ULL << c1) | (1ULL << f1) | (1ULL << c8) | (1ULL << f8);
    this->pieceBB[KNIGHT].getBB() = (1ULL << b1) | (1ULL << g1) | (1ULL << b8) | (1ULL << g8);
    this->pieceBB[ROOK].getBB() = (1ULL << a1) | (1ULL << h1) | (1ULL << a8) | (1ULL << h8);
    this->pieceBB[QUEEN].getBB() = (1ULL << d1) | (1ULL << d8);
    this->pieceBB[KING].getBB() = (1ULL << e1) | (1ULL << e8);

    this->coloredBB[WHITE].getBB() = 0xFFFFUL;
    this->coloredBB[BLACK].getBB() = 0xFFFFUL << a7;

    this->pieceBB[empty].getBB() = UINT64_MAX ^ this->fullBoard();
    this->pieceHomes = this->fullBoard();

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

void CBoard::initTestBoard()
{
    this->white_pawn_home = 0xFFUL << 8;
    this->black_pawn_home = 0xFFUL << 48;

    // en passant setup -- must make move (d7/f7 to d5/f5) first.
    this->pieceBB[PAWN].getBB()|= 0xFFUL << a7;
    this->coloredBB[BLACK].getBB() |= 0xFFUL << a7;

    this->pieceBB[PAWN].getBB() |= 1ULL << e5;
    this->coloredBB[WHITE].getBB() |= 1ULL << e5;
    

    // castling setup WHITE
    // this->pieceBB[ROOK].getBB() |= (1ULL << 0) | (1ULL << 7);
    // this->coloredBB[WHITE].getBB() |= (1ULL << 0) | (1ULL << 7);
    // this->pieceBB[KING].getBB() |= (1ULL << 4);
    // this->coloredBB[WHITE].getBB() |= (1ULL << 4);
    // // BLACK
    // this->pieceBB[ROOK].getBB() |= (1ULL << a8) | (1ULL << h8);
    // this->coloredBB[BLACK].getBB() |= (1ULL << a8) | (1ULL << h8);
    // this->pieceBB[KING].getBB() |= (1ULL << e8);
    // this->coloredBB[BLACK].getBB() |= (1ULL << e8);

    this->pieceBB[empty].getBB() = UINT64_MAX ^ this->fullBoard();
    this->pieceHomes = this->fullBoard();

    // printBitString(this->fullBoard());
    // printBitString(this->coloredBB[BLACK]);
    // printBitString(this->pieceBB[KING]);

    this->generatePiecePossibleMoves();
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
                    if (!pawnOnHome(this, sq, color))
                    {
                        break;
                    }
                    if (isLegalRookMove(sq, target) && isInBounds(target))
                    {
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

            if (isLegalKingMove(position, target) && isInBounds(target))
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
void CBoard::genAllLegalMoves(MoveList *ml, MoveList *game_ml, int color)
{
    int opp_color = oppColor(color);
    genLegalPawnMoves(ml, game_ml, opp_color);
    genLegalBishopMoves(ml, game_ml, opp_color);
    genLegalKnightMoves(ml, game_ml, opp_color);
    genLegalRookMoves(ml, game_ml, opp_color);
    genLegalQueenMoves(ml, game_ml, opp_color);
    genLegalKingMoves(ml, game_ml, opp_color);
}

void CBoard::genLegalPawnMoves(MoveList *ml, MoveList *game_ml, int opp_color)
{
    int player_color = oppColor(opp_color);
    u64 pawns = (this->pieceBB[PAWN] & this->coloredBB[player_color]);
    int sq, target;
    int i, j;
    int count = countBits(pawns);
    int count_attacks;

    for (i = 0; i < count; i++)
    {
        if (!pawns)
        {
            printf("breaking... no pawns?\n");
            break;
        }

        // implement can't double jump over a piece
        // implement

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
                    ml->add(moveStruct(sq, target, PAWN, player_color, true, true));
                }

                if (isOpposingPiece(this, sq, target, opp_color))
                {
                    ml->add(moveStruct(sq, target, PAWN, player_color, true));
                }
            }

            // pawn pushes can't be captures
            else if (isLegalRookMove(sq, target) && isEmptySquare(this, target))
            {
                // printf("checking push at %s\n", sqToStr[target]);
                // this->legalAttackedSquares[player_color].getBB() |= (1ULL << target); pushes are never attack
                ml->add(moveStruct(sq, target, PAWN, player_color));
            }
            else
            {
                printf("Pawn move, not bishop or rook legal move... \n");
            }
            attacks ^= (1ULL << target);
        }
        // turn off the square
        pawns ^= (1ULL << sq);
    }
}

void CBoard::genLegalBishopMoves(MoveList *ml, MoveList *game_ml, int opp_color)
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
                ml->add(moveStruct(sq, target, BISHOP, player_color));
            }
            else
            {
                if (noFriendlyFire(this, sq, target, player_color))
                {
                    this->legalAttackedSquares[player_color].getBB() |= (1ULL << target);
                    ml->add(moveStruct(sq, target, BISHOP, player_color, true));
                }
            }
            attacks ^= (1ULL << target);
        }
        // turn off the square
        bishops ^= (1ULL << sq);
    }
}

void CBoard::genLegalKnightMoves(MoveList *ml, MoveList *game_ml, int opp_color)
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
                ml->add(moveStruct(sq, target, KNIGHT, player_color));
            }
            else
            {
                if (noFriendlyFire(this, sq, target, player_color))
                {
                    this->legalAttackedSquares[player_color].getBB() |= (1ULL << target);
                    ml->add(moveStruct(sq, target, KNIGHT, player_color, true));
                }
            }
            attacks ^= (1ULL << target);
        }
        // turn off the square
        knights ^= (1ULL << sq);
    }
}

void CBoard::genLegalRookMoves(MoveList *ml, MoveList *game_ml, int opp_color)
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
                ml->add(moveStruct(sq, target, ROOK, player_color));
            }
            else
            {
                if (noFriendlyFire(this, sq, target, player_color))
                {
                    this->legalAttackedSquares[player_color].getBB() |= (1ULL << target);
                    ml->add(moveStruct(sq, target, ROOK, player_color, true));
                }
            }
            attacks ^= (1ULL << target);
        }
        // turn off the square
        rooks ^= (1ULL << sq);
        // end process attacks ----------------------------------------------------
    }
}

void CBoard::genLegalQueenMoves(MoveList *ml, MoveList *game_ml, int opp_color)
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
            // printf("%s on %s to %s is%slegal\n", pieceToStr[QUEEN], sqToStr[sq], sqToStr[target], (canCapture(this, sq, target, QUEEN, BLACK)) ? " " : " NOT ");
            if (isEmptySquare(this, target))
            {
                this->legalAttackedSquares[player_color].getBB() |= (1ULL << target);
                ml->add(moveStruct(sq, target, QUEEN, player_color));
            }
            else
            {
                if (noFriendlyFire(this, sq, target, player_color))
                {
                    this->legalAttackedSquares[player_color].getBB() |= (1ULL << target);
                    ml->add(moveStruct(sq, target, QUEEN, player_color, true));
                }
            }
            attacks ^= (1ULL << target);
        }
        // turn off the square
        queens ^= (1ULL << sq);
    }
}

void CBoard::genLegalKingMoves(MoveList *ml, MoveList *game_ml, int opp_color)
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
        printf("someting weird. more or less than 1 king... got: %d\n", count);
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

        if (canCastleShort(sq, player_color))
        {
            ml->add(moveStruct(sq, 0, KING, player_color, 0, 0, 1, 0));
        }

        if (canCastleLong(sq, player_color))
        {
            ml->add(moveStruct(sq, 0, KING, player_color, 0, 0, 0, 1));
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
                ml->add(moveStruct(sq, target, KING, player_color));
            }
            else
            {
                if (noFriendlyFire(this, sq, target, player_color))
                {
                    this->legalAttackedSquares[player_color].getBB() |= (1ULL << target);
                    ml->add(moveStruct(sq, target, KING, player_color, true));
                }
            }
            attacks ^= (1ULL << target);
        }
        // turn off the square
        king ^= (1ULL << sq);
    }
}

bool CBoard::canCastleShort(int sq, int color)
{
    // u64 rooks = (this->pieceBB[ROOK] & this->coloredBB[color]);
    int rookSq = (color) ? a1 : a8;
    bool everyoneAtHome = (((1ULL << rookSq) & this->pieceHomes) >= 1) && (((1ULL << sq) & this->pieceHomes) >= 1);
    bool pathIsClear;
    // also need to make sure we're not in check currently
    bool pathIsSafe;

    if (color)
    {
        pathIsClear = isEmptySquare(this, f1) && isEmptySquare(this, g1);
        pathIsSafe = !squareIsAttacked(this, f1, color) && !squareIsAttacked(this, g1, color);
    }
    else
    {
        pathIsClear = isEmptySquare(this, f8) && isEmptySquare(this, g8);
        pathIsSafe = !squareIsAttacked(this, f8, color) && !squareIsAttacked(this, g8, color);
    }
    return everyoneAtHome && pathIsSafe && pathIsClear;
}

bool CBoard::canCastleLong(int sq, int color)
{
    int rookSq = (color) ? h1 : h8;
    bool everyoneAtHome = (((1ULL << rookSq) & this->pieceHomes) >= 1) && (((1ULL << sq) & this->pieceHomes) >= 1);
    bool pathIsSafe;
    bool pathIsClear;
    if (color)
    {
        pathIsClear = isEmptySquare(this, b1) && isEmptySquare(this, c1) && isEmptySquare(this, d1);
        pathIsSafe = !squareIsAttacked(this, b1, color) && !squareIsAttacked(this, c1, color) && !squareIsAttacked(this, d1, color);
    }
    else
    {
        pathIsClear = isEmptySquare(this, b8) && isEmptySquare(this, c8) && isEmptySquare(this, d8);
        pathIsSafe = !squareIsAttacked(this, b8, color) && !squareIsAttacked(this, c8, color) && !squareIsAttacked(this, d8, color);
    }
    return everyoneAtHome && pathIsSafe && pathIsClear;
}