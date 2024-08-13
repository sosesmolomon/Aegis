#include "CBoard.h"

u64 CBoard::fullBoard() {
    return this->whitePawns | this->whiteBishops | this->whiteKnights | this->whiteRooks | this->whiteQueens | this->whiteKing | this->blackPawns | this->blackBishops | this->blackKnights | this->blackRooks | this->blackQueens | this->blackKing;
}

u64 CBoard::whitePieces()
{
    return this->whitePawns | this->whiteBishops | this->whiteKnights | this->whiteRooks | this->whiteQueens | this->whiteKing;
}
u64 CBoard::blackPieces()
{
    return this->blackPawns | this->blackBishops | this->blackKnights | this->blackRooks | this->blackQueens | this->blackKing;
}