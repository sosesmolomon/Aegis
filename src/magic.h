#ifndef MAGIC_H
#define MAGIC_H

#include "CBoard.h"


struct sMagic
{
    u64 mask; // attacks based on emptyboard
    u64 magic;
    int shift;
};
u64 getBishopAttacks(int sq, u64 occ);

u64 getRookAttacks(int sq, u64 occ);

void initMagic(CBoard *board);

void init_sliders_attacks(CBoard *b, int bishop);
#endif