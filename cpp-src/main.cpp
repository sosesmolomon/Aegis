#include <cmath>
#include <stdio.h>
#include "print.h"
#include "CBoard.h"
#include "init.h"
// a1 - a8, b1, h1 - h8
//  0 - 7,  8,  56 - 63


int main()
{

    CBoard *board = initCBoard();

    generateMagicBBs(board);

    for (int i = 0; i < 64; i++)
    {
        printf("%d:\n", i);
        printBitString(board->rookMagicBBs[i]);
    }
    return 0;
}
