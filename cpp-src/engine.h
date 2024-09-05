#ifndef ENGINE_H
#define ENGINE_H

#include "CBoard.h"
#include "MoveList.h"


float* evaluateMoveList(CBoard *b, MoveList *possible_moves, MoveList *game);

#endif