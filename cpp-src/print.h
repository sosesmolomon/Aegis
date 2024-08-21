#ifndef PRINT_H
#define PRINT_H

#include <stdint.h>
#include <stdio.h>

extern char const *sqToStr[64];

extern char const *pieceToStr[6];

extern char const *colorToStr[2];

bool printIndividualBit(uint64_t num, int position);

void printSquare();

void printBitString(uint64_t piece_type);
void printBitString(uint64_t piece_type, int square);

// Function to print a scalar array
void printScalarArray(const char* name, int* scalarArray);

void printPossibleMoves(int* possible_moves, int position);

#endif