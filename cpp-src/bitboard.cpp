#include "bitboard.h"
#include "print.h"

int count(u64 b) {
    int count = 0;
    while (b)
    {
        count++;
        b &= b - 1; // reset LS1B
    }
    return count;
}


void clearSq(u64 *b, int pos) {
    *b ^= (1ULL << pos);
}

void setSq(u64 *b, int pos) {
    *b |= (1ULL << pos);
}

bool test(u64 b, int pos) {}