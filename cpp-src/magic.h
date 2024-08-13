#include "CBoard.h"

typedef struct sMagic
{
    u64 *attacks;
    u64 mask; // attacks based on emptyboard
    u64 magic;
    int shift;
}sMagic;

u64 getAttacks(CBoard *board, enumSquare sq);

void initMagic(CBoard *board);
