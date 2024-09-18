#include "evaluate.h"
#include "move.h"
#include "engine.h"
#include "print.h"
#include "utils.h"

void evaluateMoveList(CBoard *b, MoveList *legals, MoveList *game, std::vector<float> *evals)
{
    if (legals->size() <= 0)
    {
        printf("no moves to evaluate...\n");
        return;
    }
    evals->clear();
    moveStruct m;
    float eval;

    MoveList new_poss = MoveList();
    MoveList new_legals = MoveList();

    for (int i = 0; i < legals->size(); i++)
    {
        m = legals->at(i);

        makeMove(b, m, game);

        b->genAllLegalMoves(NULL, game, m.pC, true); // clears and resets blacks attacked squares
        
        if (m.pT == QUEEN && m.to == f5) {
            printf("here\n");
            printBitString(b->legalAttackedSquares[BLACK], m.to);
        };

        printf("========================================================\n");
        updateMoveLists(b, &new_poss, game, (m.pC ^ WHITE), &new_legals);

        printf("========================================================\n");
        

        
        eval = evaluatePosition(b, &new_legals);


        if (m.pT == QUEEN && m.to == f5) {
            printf("value = %f, is in check = %d\n", eval, int(b->isInCheck(WHITE)));
            printBoard(b, b->fullBoard());



            printBitString(b->legalAttackedSquares[BLACK], m.to);
            b->genAllLegalMoves(NULL, game, m.pC, true);
            printBitString(b->legalAttackedSquares[BLACK], m.to);
            new_legals.print();

            exit(1);
        }

        evals->push_back(eval);

        undoMove(b, m, game); // I'm not sure I want to undo here...
                              // how can I go deeper?
                              // maybe this will fix itself as I implement minimax()
                              // maybe a stack of moves to undo? that gets passed around minimax?
        // printf("board after undo-move -- eval = %f\n", evaluatePosition(b));
        // printBoard(b, b->fullBoard());
        // printf("---------------------------------------------\n");
    }
}

int minimax(CBoard *b, MoveList *game, int depth, int max_depth, int turn)
{
    if (depth >= max_depth)
    {
        return 0;
    }
    return 0;
}

int bestMoveIndex(CBoard *b, MoveList *possible_moves, MoveList *game, int color)
{
    if (possible_moves->size() <= 0)
    {
        printf("HEY! NO moves????\n");
        return 0.0;
    }
    float minimax;
    float curr;
    int bestI;

    std::vector<float> evals;
    evaluateMoveList(b, possible_moves, game, &evals);

    // printf("size of legals = %lu\n", possible_moves);

    printf("\n[");
    for (int i = 0; i < evals.size(); i++)
    {
        printf("%f, ", evals.at(i));
    }
    printf("]\n\n");

    printf("checkmate moves:\n");
    for (int i = 0; i < evals.size(); i++)
    {
        moveStruct m = possible_moves->at(i);
        if (evals.at(i) == -100000 || evals.at(i) == 100000)
        {
            printf("%s %s from %s to %s\n", colorToStr[m.pC], pieceToStr[m.pT], sqToStr[m.from], sqToStr[m.to]);
        }
    }

    if (color == WHITE)
    {
        minimax = -10000000;

        for (int i = 0; i < evals.size(); i++)
        {
            curr = evals.at(i);
            if (curr > minimax)
            {
                minimax = curr;
                bestI = i;
            }
        }

        printf("best = %f\n", minimax);
    }
    else
    {
        minimax = 10000000;
        for (int i = 0; i < evals.size(); i++)
        {
            curr = evals.at(i);
            if (curr < minimax)
            {
                minimax = curr;
                bestI = i;
            }
        }
        printf("best = %f\n", minimax);
    }
    return bestI;
}