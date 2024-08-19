#include "CBoard.h"

u64 CBoard::fullBoard() {
    return this->coloredBB[BLACK] | this->coloredBB[WHITE];
}
