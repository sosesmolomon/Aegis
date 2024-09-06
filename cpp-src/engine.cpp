#include "evaluate.h"
#include "move.h"
#include "engine.h"
#include "print.h"
#include "utils.h"

std::vector<float> *evaluateMoveList(CBoard *b, MoveList *possible_moves, MoveList *game, std::vector<float> *evals)
{
    if (possible_moves->size() <= 0)
    {
        printf("no moves to evaluate...\n");
        return NULL;
    }
    if (evals->size() > 0)
        evals->clear();

    moveStruct m;

    for (int i = 0; i < possible_moves->size(); i++)
    {
        m = possible_moves->at(i);
        
        printf("board BEFORE move -- eval = %f\n", evaluatePosition(b));
        printBoard(b, b->fullBoard());
        printf("---------------------------------------------\n");
        makeMove(b, m, game);

        printf("board AFTER move -- eval = %f\n", evaluatePosition(b));
        printBoard(b, b->fullBoard());
        printf("---------------------------------------------\n");
        // printf("eval for %s %s at %s capturing %s at %s is %f\n", colorToStr[m.pC], pieceToStr[m.pT], sqToStr[m.from], pieceToStr[identifyPieceType(b, m.to, (1ULL << m.to))], sqToStr[m.to], evaluatePosition(b));

        evals->push_back(evaluatePosition(b));

        undoMove(b, m, game); // I'm not sure I want to undo here...
                              // how can I go deeper?
                              // maybe this will fix itself as I implement minimax()
                              // maybe a stack of moves to undo? that gets passed around minimax?
        printf("board after undo-move -- eval = %f\n", evaluatePosition(b));
        printBoard(b, b->fullBoard());
        printf("---------------------------------------------\n");
    }
    return evals;
}

int minimax(CBoard *b, MoveList *possible_moves, MoveList *game, std::vector<float> evals, int depth, int max_depth, int turn)
{
    if (depth > max_depth)
    {
        return bestMoveIndex(b, possible_moves, game, turn);
    }

    MoveList curr_possible_moves = MoveList();

    // must do this step to fill the attacked squares
    b->genAllLegalMoves(&curr_possible_moves, game, WHITE);
    b->genAllLegalMoves(&curr_possible_moves, game, BLACK);

    // get the possible moves for curr player's turn
    updateMoveLists(b, &curr_possible_moves, game, turn);

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

void updateMoveLists(CBoard *b, MoveList *possible_moves, MoveList *game, int color)
{
    possible_moves->clear();
    b->legalAttackedSquares[color].getBB() = 0ULL;
    b->genAllLegalMoves(possible_moves, game, color);
    // removeChecks();
    // walk through the move list and determine if any of the moves results
    // in the current player being in check,
    // if they do, remove this from the movelist

    // if currently in check
    // walk through the movelist and remove anything that
    // doesn't take the player out of check

    // if moveList is 0, checkmate
}

int bestMoveIndex(CBoard *b, MoveList *possible_moves, MoveList *game, int color)
{
    if (possible_moves->size() <= 0)
    {
        printf("HEY! NO moves????\n");
        return 0.0;
    }
    float minimax = 0;
    float curr;
    int bestI;

    std::vector<float> evals;
    evals = *evaluateMoveList(b, possible_moves, game, &evals);

    printf("\n[");
    for (int i = 0; i < evals.size(); i++)
    {
        printf("%f, ", evals.at(i));
    }
    printf("]\n\n");

    if (color == WHITE)
    {

        for (int i = 0; i < evals.size(); i++)
        {
            curr = evals.at(i);
            if (curr > minimax)
            {
                minimax = curr;
                bestI = i;
            }
        }
    }
    else
    {
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