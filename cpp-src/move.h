#ifndef MOVE_H
#define MOVE_H

#include "CBoard.h"

class Move
{
};

// should from and to be u64 or ints? what is actually changing?
void makeMove(CBoard *b, int from, int to, int pieceType, color color);



#endif 