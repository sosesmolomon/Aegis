#ifndef MOVE_H
#define MOVE_H

#include "MoveList.h"
#include "CBoard.h"

bool movesAreEqual(moveStruct m1, moveStruct m2);

void makeDefinedMove(CBoard *b, moveStruct m, MoveList *possible_moves, MoveList *game);

// should from and to be u64 or ints? what is actually changing?
void makeMove(CBoard *b, moveStruct m, MoveList *game);

void undoMove(CBoard *b, moveStruct m, MoveList *game);

void undoLastMove(CBoard *b, MoveList *game);




#endif 