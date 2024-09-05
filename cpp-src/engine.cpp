#include "evaluate.h"
#include "move.h"

std::vector<float> *evaluateMoveList(CBoard *b, MoveList *possible_moves, MoveList *game, std::vector<float> *evals) {
    if (possible_moves->size() <= 0) {
        printf("no moves to evaluate...\n");
        return NULL;
    }
    if (evals->size() > 0)
        evals->clear();

    moveStruct m;

    for (int i = 0; i < possible_moves->size(); i++) {
        m = possible_moves->at(i);

        makeMove(b, m, game);
        evals->push_back(evaluatePosition(b));
        undoMove(b, m, game);     
    }
    return evals;
}