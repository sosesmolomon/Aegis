#include "print.h"

bool printIndividualBit(uint64_t num, int position)
{
    uint64_t mask = 1ULL << position;

    uint64_t isolated_bit = num & mask;
    return isolated_bit ? 1 : 0;
}

void printSquare()
{
    for (int i = 0; i < 64; i++)
    {
        printf("%s ", square_names[i]);
        if ((i + 1) % 8 == 0)
        {
            printf("\n");
        }
    }
}

// smartly prints
// h1 - h8
// ...
// a1 - a8
void printBitString(uint64_t bitboard)
{
    int start;
    for (int i = 1; i < 9; i++)
    {
        start = (i * 8) - 1;

        for (int pos = start; pos > start - 8; pos--)
        {
            // printf("%d ", pos);
            printf("%d ", printIndividualBit(bitboard, pos));
            // if (bit)
            //     printf("1");
            // else
            //     printf("0");
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void printPossibleMoves(int *possible_moves, int position)
{
    // possible moves = [-16, -10, 10, 12]
    // position = 48
    printf("\n");
    uint64_t square = 1ULL << position;

    int shift;
    int target;
    for (int i = 0; i < 56; i++)
    {
        if (possible_moves[i] == 0)
            break;
        shift = possible_moves[i];
        target = position + shift;
        square = square | (1ULL << target);
    }

    printBitString(square);
}

// Function to print a scalar array
void printScalarArray(const char *name, int *scalarArray)
{
    printf("%s:\n", name);
    for (int i = 0; i < 64; ++i)
    {
        printf("%d ", scalarArray[i]);
        if ((i + 1) % 8 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
}