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


    for (int i = 0; i < legals->size(); i++)
    {
        m = legals->at(i);

        // printf("board BEFORE move -- eval = %f\n", evaluatePosition(b));
        // printBoard(b, b->fullBoard());
        // printf("---------------------------------------------\n");

        makeMove(b, m, game);

        // printf("board AFTER move -- eval = %f\n", evaluatePosition(b));
        // printBoard(b, b->fullBoard());
        // printf("---------------------------------------------\n");
        // printf("eval for %s %s at %s capturing %s at %s is %f\n", colorToStr[m.pC], pieceToStr[m.pT], sqToStr[m.from], pieceToStr[identifyPieceType(b, m.to, (1ULL << m.to))], sqToStr[m.to], evaluatePosition(b));
        eval = evaluatePosition(b);
        b->genAllLegalMoves(NULL, game, m.pC, true);
        if (b->isInCheck(m.pC^WHITE)) {
            eval *= 3; // multiplying by an odd number will keep negatives as negatives
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

int minimax(CBoard *b, MoveList *possible_moves, MoveList *game, std::vector<float> evals, int depth, int max_depth, int turn)
{
    if (depth > max_depth)
    {
        return bestMoveIndex(b, possible_moves, game, turn);
    }

    MoveList curr_possible_moves = MoveList();

    // must do this step to fill the attacked squares
    b->genAllLegalMoves(&curr_possible_moves, game, WHITE, true);
    b->genAllLegalMoves(&curr_possible_moves, game, BLACK, true);

    // get the possible moves for curr player's turn
    updateMoveLists(b, &curr_possible_moves, game, turn, possible_moves); // BAD

    // iterate through the possible_moves... how does this work when possible moves will change sizes?
    // call minimax on each move
    // return either max() or min() of evals

    for (int i = 0; i < curr_possible_moves.size(); i++)
    {
        // pass in curr_possible as possible_moves... the child call will create a new curr_possible_moves
        minimax(b, &curr_possible_moves, game, evals, depth++, max_depth, (turn ^ WHITE));
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



    if (color == WHITE)
    {
        minimax = -100000;
        printf("here\n");

        for (int i = 0; i < evals.size(); i++)
        {
            curr = evals.at(i);
            if (curr > minimax)
            {
                minimax = curr;
                bestI = i;
            }
        }

        printf("%f\n", minimax);
    }
    else
    {
        minimax = 100000;
        for (int i = 0; i < evals.size(); i++)
        {
            curr = evals.at(i);
            if (curr < minimax)
            {
                minimax = curr;
                bestI = i;
            }
        }
    }
    return bestI;
}