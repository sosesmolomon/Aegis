#ifndef POSITION_H
#define POSITION_H

#include "CBoard.h"
#include "MoveList.h"

// is this also a MoveList?
void genAllLegalMoves(CBoard *b, MoveList *ml, int color);

void genLegalPawnMoves(CBoard *b);
void genLegalBishopMoves(CBoard *b, int opp_color);
void genLegalKnightMoves(CBoard *b, int opp_color);
void genLegalRookMoves(CBoard *b, int opp_color);
void genLegalQueenMoves(CBoard *b, int opp_color);
void genLegalKingMoves(CBoard *b, int opp_color);




#endif