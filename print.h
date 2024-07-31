#ifndef PRINT_H
#define PRINT_H
#include "typedefs.h"
#include "utils.h"
#include "init.h"

bool printIndividualBit(uint64_t num, int position);

void printSquare();

void printBitString(uint64_t piece_type);

// Function to print a scalar array
void printScalarArray(const char* name, int* scalarArray);

#endif