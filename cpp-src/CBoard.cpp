#include "CBoard.h"
#include "bitboard.h"
#include <stdio.h>

u64 CBoard::fullBoard() {
    return this->coloredBB[BLACK].b | this->coloredBB[WHITE].b;
}

u64 CBoard:: wP() {
    return this->pieceBB[PAWN].b&this->coloredBB[WHITE].b;
}

u64 CBoard:: wB() {
    return this->pieceBB[BISHOP].b&this->coloredBB[WHITE].b;
}

u64 CBoard:: wKn() {
    return this->pieceBB[KNIGHT].b&this->coloredBB[WHITE].b;
}
u64 CBoard:: wR() {
    return this->pieceBB[ROOK].b&this->coloredBB[WHITE].b;
}
u64 CBoard:: wQ() {
    return this->pieceBB[QUEEN].b&this->coloredBB[WHITE].b;
}
u64 CBoard:: wK() {
    return this->pieceBB[KING].b&this->coloredBB[WHITE].b;
}

u64 CBoard:: bP() {
    return this->pieceBB[PAWN].b&this->coloredBB[BLACK].b;
}

u64 CBoard:: bB() {
    return this->pieceBB[BISHOP].b&this->coloredBB[BLACK].b;
}

u64 CBoard:: bKn() {
    return this->pieceBB[KNIGHT].b&this->coloredBB[BLACK].b;
}
u64 CBoard:: bR() {
    return this->pieceBB[ROOK].b&this->coloredBB[BLACK].b;
}
u64 CBoard:: bQ() {
    return this->pieceBB[QUEEN].b&this->coloredBB[BLACK].b;
}
u64 CBoard:: bK() {
    return this->pieceBB[KING].b&this->coloredBB[BLACK].b;
}