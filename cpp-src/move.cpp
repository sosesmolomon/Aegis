#include "move.h"
#include "CBoard.h"
#include "bitboard.h"
#include "print.h"
#include "utils.h"
#include "MoveList.h"
#include <cassert>

bool movesAreEqual(moveStruct m1, moveStruct m2)
{
    return (m1.from == m2.from) && (m1.to == m2.to) && (m1.pT == m2.pT) && (m1.pC == m2.pC) && (m1.isCapture == m2.isCapture) && (m1.isEnPassant == m2.isEnPassant) && (m1.isCastlingShort == m2.isCastlingShort) && (m1.isCastlingLong == m2.isCastlingLong);
}

void makeDefinedMove(CBoard *b, moveStruct m, MoveList *possible_moves, MoveList *game)
{
    if (possible_moves->size() <= 0)
    {
        return;
    }

    for (int i = 0; i < possible_moves->size(); i++)
    {
        if (movesAreEqual(m, possible_moves->at(i)))
        {
            // printf("move %s %s to %s at index = %d\n", pieceToStr[m.pT], sqToStr[m.from], sqToStr[m.to], i);
            makeMove(b, m, game);
            return;
        }
    }
    printf("MOVE DIDN'T EXIST for %s from %s to %s\n", pieceToStr[m.pT], sqToStr[m.from], sqToStr[m.to]);
}

// based on a move_list of legal moves
void makeMove(CBoard *b, moveStruct m, MoveList *game)
{
    assert((b->pieceBB[m.pT] & (1ULL << m.from)) >= 1 && "Piece mismatch");
    assert((b->coloredBB[m.pC] & (1ULL << m.from)) >= 1 && "Color mismatch");

    // Save current castling rights
    b->castlingRightsStack.push(b->currentCastlingRights);
    // Update castling rights based on the move
    b->updateCastlingRights(m);

    if (m.isCastlingShort || m.isCastlingLong || m.isPromotion)
    {
        if (m.isPromotion)
        {
            b->setSq(empty, m.pC, m.from);
            b->setSq(QUEEN, m.pC, m.to);
        }
        else
        {
            if (m.isCastlingShort)
            {
                // white short
                if (m.pC)
                {
                    b->setSq(empty, WHITE, e1);
                    b->setSq(empty, WHITE, h1);

                    b->setSq(KING, WHITE, g1);
                    b->setSq(ROOK, WHITE, f1);
                }
                // black short
                else
                {
                    b->setSq(empty, BLACK, e8);
                    b->setSq(empty, BLACK, h8);

                    b->setSq(KING, BLACK, g8);
                    b->setSq(ROOK, BLACK, f8);
                }
            }
            else
            {
                // white long
                if (m.pC)
                {
                    b->setSq(empty, WHITE, e1);
                    b->setSq(empty, WHITE, a1);

                    b->setSq(KING, WHITE, c1);
                    b->setSq(ROOK, WHITE, d1);
                }
                // black long
                else
                {
                    b->setSq(empty, BLACK, e8);
                    b->setSq(empty, BLACK, a8);

                    b->setSq(KING, BLACK, c8);
                    b->setSq(ROOK, BLACK, d8);
                }
            }
        }
    }
    else
    {
        // if ((b->coloredBB[m.pC] & (1ULL << m.to)) == 1) {
        //     m.toString();
        // }
        // assert((b->coloredBB[m.pC] & (1ULL << m.to)) == 1 && "Capture same color");

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
    }
    game->add(m);
}


// quiet move, no capture...
void undoMove(CBoard *b, moveStruct m, MoveList *game)
{
    if (m.isCastlingShort || m.isCastlingLong || m.isPromotion)
    {
        if (m.isPromotion)
        {
            b->setSq(PAWN, m.pC, m.from);
            b->setSq(empty, m.pC, m.to);
        }
        else
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
                    b->setSq(KING, BLACK, e8);
                    b->setSq(ROOK, BLACK, h8);

                    b->setSq(empty, BLACK, g8);
                    b->setSq(empty, BLACK, f8);
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
                    b->setSq(KING, BLACK, e8);
                    b->setSq(ROOK, BLACK, a8);

                    b->setSq(empty, BLACK, c8);
                    b->setSq(empty, BLACK, d8);
                }
            }
        }
    }
    else
    {
        b->setSq(empty, m.pC, m.to);

        // assert((b->coloredBB[m.pC] & 1ULL << m.to) == 0 && "Capture same color");

        // is capture?
        if (m.isCapture)
        {
            int opp_piece_sq = m.to;
            if (m.isEnPassant)
            {
                // a little scary to be backwards indexing by 2 here... however, the move must exist if en passant is a legal move
                opp_piece_sq = game->at(game->size() - 2).to;
            }
            // turn the pawn back on before en passant capture
            b->setSq(m.capturedP, (m.pC ^ WHITE), opp_piece_sq);
        }

        b->setSq(m.pT, m.pC, m.from);
    }

    if (!b->castlingRightsStack.empty()) {
        b->currentCastlingRights = b->castlingRightsStack.top();
        b->castlingRightsStack.pop();
    } else {
        printf("stack underflow?\n");
    }

    game->remove(game->size() - 1); // remove just the end of the list?
}

void undoLastMove(CBoard *b, MoveList *game)
{
    if (game->size() == 0)
    {
        printf("no more moves to undo\n");
        return;
    }
    undoMove(b, game->at(game->size() - 1), game);
}