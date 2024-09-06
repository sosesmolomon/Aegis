#ifndef ENGINE_H
#define ENGINE_H

#include "CBoard.h"
#include "MoveList.h"


std::vector<float> *evaluateMoveList(CBoard *b, MoveList *possible_moves, MoveList *game, std::vector<float> *evals);

int minimax(CBoard *b, MoveList *possible_moves, MoveList *game, std::vector<float> evals, int depth, int max_depth, int turn);

void updateMoveLists(CBoard *b, MoveList *possible_moves, MoveList *game, int color);

int bestMoveIndex(CBoard *b, MoveList *possible_moves, MoveList *game, int color);

#endif