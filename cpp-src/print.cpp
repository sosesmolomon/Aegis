#include "print.h"


char const *sqToStr[64] = {
    "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8",
    "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8",
    "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8",
    "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8",
    "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8",
    "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8",
    "g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8",
    "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8"};

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