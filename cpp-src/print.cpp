#include "print.h"

char const *sqToStr[64] = {
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
     "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
     "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
     "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
     "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
     "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
     "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
     "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"};

char const *pieceToStr[7] = {
    "PAWN", "BISHOP", "KNIGHT", "ROOK", "QUEEN", "KING", "empty"};

char const *colorToStr[2] = {
    "BLACK", "WHITE"};

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
        // printf("%s ", square_names[i]);
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
    for (int i = 8; i > 0; i--)
    {

        start = (i * 8) - 8; // 56

        for (int pos = start; pos < start + 8; pos++)
        {
            printf("%d ", printIndividualBit(bitboard, pos));
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void printBitString(uint64_t bitboard, int square)
{
    int start;
    for (int i = 8; i > 0; i--)
    {

        start = (i * 8) - 8; // 56

        for (int pos = start; pos < start + 8; pos++)
        {
            if (pos == square)
            {
                printf("x ");
            }
            else
            {
                printf("%d ", printIndividualBit(bitboard, pos));
            }
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