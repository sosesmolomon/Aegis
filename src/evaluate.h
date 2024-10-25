#ifndef EVALUATE_H
#define EVALUATE_H

#include "CBoard.h"
#include "MoveList.h"


float evaluatePosition(CBoard *b, MoveList *legals);

#endif