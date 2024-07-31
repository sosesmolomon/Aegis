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
    char row[8] = "00000000";
    int counter = 7;
    for (int i = 1; i < 65; i++)
    {
        bool bit = printIndividualBit(bitboard, i - 1);
        if (bit)
            row[counter] = '1';
        else
            row[counter] = '0';
        counter--;

        // strcat(&row, &bit);

        if (i % 8 == 0)
        {
            // printf("\n");
            // printf("on row: %d", i);
            int len = strlen(row);

            // Print the string up to the second-to-last character
            printf("%.*s\n", len - 1, row);
            counter = 7;
        }
    }
}

// Function to print a scalar array
void printScalarArray(const char* name, int* scalarArray) {
    printf("%s:\n", name);
    for (int i = 0; i < 64; ++i) {
        printf("%d ", scalarArray[i]);
        if ((i + 1) % 8 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}