#include "evaluate.h"
#include "utils.h"
#include "print.h"

// new eval
// put them on squares with more options
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

int multiplier[] = {1, 1, 1, 1, 1, 1, 1};

float evalWhite(CBoard *b)
{
    int eval = 0;
    int *scalar;
    int count;
    int sq, i;
    u64 pieceBB;

    for (int pT = PAWN; pT < empty; pT++)
    {
        scalar = scalars[pT];
        pieceBB = b->pieceBB[pT] & b->coloredBB[WHITE];
        count = countBits(pieceBB);

        for (i = 0; i < count; i++)
        {
            sq = firstOne(pieceBB);
            eval += (scalar[sq] * multiplier[pT]);
            // printf("WHITE eval +%d for piece %s at %s\n", scalar[sq] * multiplier[pT], pieceToStr[pT], sqToStr[sq]);
        }
    }

    printf("\n");
    return eval;
}
float evalBlack(CBoard *b)
{
    int eval = 0;
    int *scalar;
    int count;
    int sq, i;
    u64 pieceBB;

    for (int pT = PAWN; pT < empty; pT++)
    {
        scalar = scalars[pT];
        pieceBB = b->pieceBB[pT] & b->coloredBB[BLACK];
        count = countBits(pieceBB);

        for (i = 0; i < count; i++)
        {
            sq = firstOne(pieceBB);
            eval += (scalar[63 - sq] * multiplier[pT]);
            // printf("BLACK eval +%d for piece %s at %s, index = %d\n", scalar[63 - sq] * multiplier[pT], pieceToStr[pT], sqToStr[sq], 63-sq);
            pieceBB ^= (1ULL << sq);
        }
    }
    printf("\n");
    return -eval;
}

float evaluatePosition(CBoard *b)
{
    float eval = 0;
    float white_eval, black_eval;
    int *scalar;
    int count;
    int sq, i;
    u64 pieceBB;
    int start, end;

    white_eval = evalWhite(b);
    black_eval = evalBlack(b);

    printf("\nwhite eval= %f\nblack_eval = %f\n", white_eval, black_eval);

    return white_eval + black_eval;
}