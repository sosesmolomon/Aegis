#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "print.h"

// Brian Kernighans method 
int popCount(uint64_t x)
{
    int count = 0;
    while (x)
    {
        count++;
        // printBitString(x);
        x &= x - 1; // reset LS1B
        // printBitString(x-1);
        break;
    }
    return count;
}

void BitmapTest()
{
    uint64_t pawns = 0xFFUL << 8;
    // printBitString(pawns);

    printf("count = %d\n", popCount(pawns));

    uint64_t i, j, val;
    uint64_t PowerOf2[64];

    for (i = 0; i <= 63; i++)
    {
        PowerOf2[i] = (1ULL << i);
    }

    printBitString(PowerOf2[63]);

    clock_t begin = clock();

    for (j = 1; j < 10000000; j++)
        for (i = 0; i < 64; i++)
        {
            // try using shifts
            // val = 1ULL << i;

            // try array
            val = PowerOf2[i];
        }
    printf("%llu\n", val); // needed to keep the optimizer from not doing the loops
    begin = clock() - begin;
    printf("time taken = %f\n", (float)begin / CLOCKS_PER_SEC);
}

int main()
{
    BitmapTest();
    return 0;
}
