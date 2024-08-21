#ifndef MOVE_H
#define MOVE_H

#include "MoveList.h"
#include "CBoard.h"

void genAllLegalMoves(CBoard *b, MoveList *ml);

// should from and to be u64 or ints? what is actually changing?
void makeMove(CBoard *b, int from, int to, int pieceType, int color);



#endif 