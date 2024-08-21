#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>

typedef uint64_t u64;

class Bitboard
{
public:
    u64 b;

    int count();

    void clearSq(int pos);

    void setSq(int pos);

    bool test(int pos);

    // Overload the u64 operator
    operator u64() const;

    u64& getBB();

};
#endif