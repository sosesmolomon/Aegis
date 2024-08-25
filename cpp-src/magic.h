#ifndef MAGIC_H
#define MAGIC_H

#include "CBoard.h"


typedef struct sMagic
{
    u64 *attacks;
    u64 mask; // attacks based on emptyboard
    u64 magic;
    int shift;
}sMagic;

sMagic mBishopTab[64];
sMagic mRookTab[64];    


u64 getBishopAttacks(int sq, u64 occ);

u64 getRookAttacks(int sq, u64 occ);

void initMagic(CBoard *board);

void init_sliders_attacks(CBoard *b, int bishop);
#endif