#ifndef INIT_H
#define INIT_H

#include "CBoard.h"


CBoard *initCBoard();

bool canCapture();
bool pawnOnHomeRow();

void generatePawnPossibleMoves(CBoard *board);

bool isLegalBishopMove(int start, int end);
void generateBishopPossibleMoves(CBoard *board);

bool isLegalKnightMove(int start, int end);
void generateKnightPossibleMoves(CBoard *board);

bool isLegalRookMove(int start, int end);
void generateRookPossibleMoves(CBoard *board);

bool isLegalQueenMove(int start, int end);
void generateQueenPossibleMoves(CBoard *board);

bool isLegalKingMove(int start, int end);
void generateKingPossibleMoves(CBoard *board);


void generatePiecePossibleMoves(CBoard *board);
void removeAttackEdges(CBoard *board);

#endif