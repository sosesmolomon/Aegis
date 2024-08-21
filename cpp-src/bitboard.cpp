#include "bitboard.h"
#include "print.h"

Bitboard::operator u64() const {
    return b;
}

int Bitboard::count() {
    int count = 0;
    while (this->b)
    {
        count++;
        this->b &= this->b - 1; // reset LS1B
    }
    return count;
}

void Bitboard::clearSq(int pos) {
    this->b ^= (1ULL << pos);
}

void Bitboard::setSq(int pos) {
    this->b |= (1ULL << pos);
}

bool Bitboard::test(int pos) {
    printBitString(this->b);
    return true;
}

u64 &Bitboard::getBB() {
    return this->b;
}
