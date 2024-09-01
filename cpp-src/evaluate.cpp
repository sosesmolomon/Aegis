#include "evaluate.h"
#include "utils.h"
#include "print.h"

int scalars[6][64] = {
    {0, 0, 0, 0, 0, 0, 0, 0,
     1, 1, 1, 1, 1, 1, 1, 1,
     2, 2, 2, 2, 2, 2, 2, 2,
     3, 3, 3, 3, 3, 3, 3, 3,
     4, 4, 4, 4, 4, 4, 4, 4,
     5, 5, 5, 5, 5, 5, 5, 5,
     6, 6, 6, 6, 6, 6, 6, 6,
     7, 7, 7, 7, 7, 7, 7, 7},
    {3, 1, 1, 1, 1, 1, 1, 3,
     1, 3, 1, 1, 1, 1, 3, 1,
     1, 1, 3, 1, 1, 3, 1, 1,
     1, 2, 1, 3, 3, 1, 2, 1,
     2, 1, 2, 3, 3, 2, 1, 2,
     1, 2, 3, 1, 1, 3, 2, 1,
     1, 3, 1, 1, 1, 1, 3, 1,
     3, 1, 1, 1, 1, 1, 1, 3},
    {1, 1, 1, 1, 1, 1, 1, 1,
     1, 2, 2, 2, 2, 2, 2, 1,
     1, 2, 3, 3, 3, 3, 2, 1,
     1, 2, 3, 4, 4, 3, 2, 1,
     1, 2, 3, 4, 4, 3, 2, 1,
     1, 2, 3, 3, 3, 3, 2, 1,
     1, 2, 2, 2, 2, 2, 2, 1,
     1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 3, 3, 1, 1, 1,
     1, 1, 1, 3, 3, 1, 1, 1,
     1, 1, 1, 2, 2, 1, 1, 1,
     1, 1, 1, 2, 2, 1, 1, 1,
     1, 1, 1, 2, 2, 1, 1, 1,
     1, 1, 1, 2, 2, 1, 1, 1,
     2, 5, 5, 5, 5, 5, 5, 2,
     1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 3, 3, 2, 2, 2,
     2, 3, 3, 3, 3, 3, 3, 2,
     2, 3, 4, 4, 4, 4, 3, 2,
     3, 3, 4, 5, 5, 4, 3, 3,
     3, 3, 4, 5, 5, 4, 3, 3,
     2, 3, 4, 4, 4, 4, 3, 2,
     2, 3, 3, 3, 3, 3, 3, 2,
     2, 2, 2, 3, 3, 2, 2, 2},
    {4, 3, 2, 1, 1, 2, 3, 4,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0}};

float evaluatePosition(CBoard *b)
{
    float eval = 0;
    float white_eval, black_eval;
    int* scalar;
    int count;
    int sq, i;
    u64 pieceBB;

    for (int color = BLACK; color <= WHITE; color++)
    {
        for (int pT = PAWN; pT < empty; pT++)
        {
            scalar = (color == WHITE) ? scalars[pT] : scalars[pT]; // do I need to flip the board for white/black?
            pieceBB = b->pieceBB[pT] & b->coloredBB[color];
            count = countBits(pieceBB);
            for (i = 0; i < count; i++) {
                sq = firstOne(pieceBB);
                eval += scalar[sq];
                printf("increasing eval by %d for piece %s at square %s\n\n", scalar[sq], pieceToStr[pT], sqToStr[sq]);
                pieceBB ^= (1ULL << sq);
            }
        }
        if (color == WHITE)
            white_eval = eval;
        else 
            black_eval = -(eval);
    }
    printf("\nwhite eval= %f\nblack_eval = %f\nn", white_eval, black_eval);

    return white_eval + black_eval;
}