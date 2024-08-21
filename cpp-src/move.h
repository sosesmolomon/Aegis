#ifndef MOVE_H
#define MOVE_H

#include "CBoard.h"
#include "MoveList.h"




// void genAllLegalMoves(CBoard *b, moveStruct *ml);



// should from and to be u64 or ints? what is actually changing?
void makeMove(CBoard *b, int from, int to, int pieceType, int color);



#endif 