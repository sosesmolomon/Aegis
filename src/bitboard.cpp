#include "bitboard.h"
#include "print.h"
#include "utils.h"

Bitboard::operator u64() const
{
    return b;
}

int Bitboard::count()
{
    int count = 0;
    while (this->b)
    {
        count++;
        this->b &= this->b - 1; // reset LS1B
    }
    return count;
}

void Bitboard::clr(int pos)
{
    if (singleBit(this->b, pos))
        this->b ^= (1ULL << pos);
}

void Bitboard::set(int pos)
{
    this->b |= (1ULL << pos);
}

bool Bitboard::test(int pos)
{
    printBitString(this->b);
    return true;
}

u64 &Bitboard::getBB()
{
    return this->b;
}
