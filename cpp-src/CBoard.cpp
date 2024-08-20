#include "CBoard.h"

u64 CBoard::fullBoard() {
    return this->coloredBB[BLACK] | this->coloredBB[WHITE];
}

u64 CBoard:: wP() {
    return this->pieceBB[PAWN]&this->coloredBB[WHITE];
}

u64 CBoard:: wB() {
    return this->pieceBB[BISHOP]&this->coloredBB[WHITE];
}

u64 CBoard:: wKn() {
    return this->pieceBB[KNIGHT]&this->coloredBB[WHITE];
}
u64 CBoard:: wR() {
    return this->pieceBB[ROOK]&this->coloredBB[WHITE];
}
u64 CBoard:: wQ() {
    return this->pieceBB[QUEEN]&this->coloredBB[WHITE];
}
u64 CBoard:: wK() {
    return this->pieceBB[KING]&this->coloredBB[WHITE];
}

u64 CBoard:: bP() {
    return this->pieceBB[PAWN]&this->coloredBB[BLACK];
}

u64 CBoard:: bB() {
    return this->pieceBB[BISHOP]&this->coloredBB[BLACK];
}

u64 CBoard:: bKn() {
    return this->pieceBB[KNIGHT]&this->coloredBB[BLACK];
}
u64 CBoard:: bR() {
    return this->pieceBB[ROOK]&this->coloredBB[BLACK];
}
u64 CBoard:: bQ() {
    return this->pieceBB[QUEEN]&this->coloredBB[BLACK];
}
u64 CBoard:: bK() {
    return this->pieceBB[KING]&this->coloredBB[BLACK];
}