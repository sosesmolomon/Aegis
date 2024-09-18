#ifndef ENGINE_H
#define ENGINE_H

#include "CBoard.h"
#include "MoveList.h"


void evaluateMoveList(CBoard *b, MoveList *possible_moves, MoveList *game, std::vector<float> *evals);

int minimax(CBoard *b, MoveList *game, int depth, int max_depth, int turn);

int bestMoveIndex(CBoard *b, MoveList *possible_moves, MoveList *game, int color);

#endif