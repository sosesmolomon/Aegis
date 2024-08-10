#include "CBoard.h"


CBoard *initCBoard();
bool isLegalBishopMove(int start, int end);
void generateBishopMagicBBs(CBoard *board);
bool isLegalRookMove(int start, int end);
void generateRookMagicBBs(CBoard *board);

void generateMagicBBs(CBoard *board);