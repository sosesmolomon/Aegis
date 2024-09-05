#ifndef ENGINE_H
#define ENGINE_H

#include "CBoard.h"
#include "MoveList.h"


std::vector<float> *evaluateMoveList(CBoard *b, MoveList *possible_moves, MoveList *game, std::vector<float> *evals);

#endif