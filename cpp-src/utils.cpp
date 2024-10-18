#include "utils.h"
#include "print.h"
#include <math.h>
#include <cassert>
#include <iostream>
#include <string>
#include <cctype>

#include "CBoard.h"

int identifyPieceType(CBoard *b, int sq)
{
    u64 mask;

    for (int i = 0; i < nPieceT + 1; i++)
    {
        mask = (b->pieceBB[i] & (1ULL << sq));
        if (mask >= 1)
        {
            return i;
        }
    }
    // printf("no piece type in square %d", sq);
    return empty;
}
int identifyPieceColor(CBoard *b, int sq)
{
    u64 mask;
    for (int i = 0; i < 3; i++)
    {
        mask = b->coloredBB[i];
        if ((mask & (1ULL << sq)) >= 1)
            return i;
    }
    return -1;
}

int getRow(int sq)
{
    // printf("file = %d\n", (sq / 8) + 1);
    return (int(floor(sq / 8) + 1));
}

int getFile(int sq)
{
    // printf("file = %d\n", (sq % 8) + 1);
    return (sq % 8) + 1;
}

bool squareIsAttacked(CBoard *b, int sq, int color)
{
    // need more here.
    // this is for checks.
    return ((1ULL << sq) & b->legalAttackedSquares[(color ^ WHITE)]) >= 1;
}
bool pieceIsDefended(CBoard *b, int sq, int color) {}

bool pawnOnHome(CBoard *b, int sq, int color)
{
    u64 square = (1ULL << sq);
    // printf("color = %s\n", colorToStr[color]);

    // printf("check = %d", int(square & b->white_pawn_home));
    if (color)
        return ((square & b->white_pawn_home) >= 1);
    else
        return ((square & b->black_pawn_home) >= 1);
}

bool singleBit(u64 b, int sq)
{
    b &= (1ULL << sq);
    return b >= 1;
}

bool isEmptySquare(CBoard *b, int square)
{
    u64 mask = 1ULL << square;
    return ((mask & b->fullBoard()) >= 1) ? 0 : 1;
}

bool isInBounds(int square)
{
    if (square >= 64 | square < 0)
        return false;
    return true;
};

int countBits(u64 b)
{
    int r = 0;

    while (b)
    {
        b &= b - 1;
        r++;
    }
    return r;
}

int oppColor(int color)
{
    return color ^= WHITE;
}

int firstOne(u64 &b)
{
    if (b == 0)
    {
        return 64; // No bits are set
    }

    // Find the position of the least significant 1-bit
    int bit = __builtin_ctzll(b); // Use GCC/Clang built-in function for counting trailing zeros

    // Clear the least significant 1-bit
    b &= (b - 1);

    return bit;
}

int lastOne(u64 b)
{
    int n = 63;
    u64 max = (1ULL << h8);

    if (b)
    {
        while ((b & max) == 0)
        {
            n--;
            b <<= 1;
        }
    }

    return n;
}

bool isOpposingPiece(CBoard *b, int start, int target, int opp_color)
{
    if ((b->coloredBB[opp_color] & (1ULL << target)) >= 1)
    {
        return true;
    }
    return false;
}

bool noFriendlyFire(CBoard *b, int start, int target, int player_color)
{
    if ((b->coloredBB[player_color] & (1ULL << target)) >= 1)
    {
        return false;
    }
    return true;
}

// check that the last move in the game was:
// played by the opponent
// was a PAWN double move
// file is adjacent to current file
bool canEnPassant(MoveList *game, int sq, int target, int player_color)
{
    // sq = the capturing pawns current square
    if (game->size() < 1)
        return false;

    int index = game->size() - 1;
    moveStruct move = game->at(index);

    // must be a double move
    if (abs(move.to - move.from) == 16 && move.pT == PAWN && move.pC == (player_color ^ WHITE))
    {
        // opp pawn double moves and sits next to player pawn.     ensure looking at correct side of pawn
        if ((abs(getRow(move.to) - getRow(sq)) == 0) && ((getFile(move.to) - getFile(target)) == 0))
        {
            return true;
        }
    }
    return false;
}

void updateMoveLists(CBoard *b, MoveList *possible_moves, MoveList *game, int color, MoveList *legal_moves)
{
    possible_moves->clear();
    legal_moves->clear();
    b->genAllLegalMoves(possible_moves, game, color, false);
    printf("----------------^gen legals^----------------\n");
    b->verifyLegalMoves(possible_moves, game, color, legal_moves);
    printf("----------------^verify legals^----------------\n");
}

// 	for fr := frBB.firstOne();
// fr != 64;
// fr = frBB.firstOne()
// {
//     atkBB |= atksKnights[fr]
// }
// }


int squareEnumFromStr(const std::string& sqStr) {
    if (sqStr.length() != 2) {
        // Handle invalid input length
        std::cerr << "Invalid square string length: " << sqStr << std::endl;
        return -1;
    }
    
    char fileChar = std::tolower(sqStr[0]);
    char rankChar = sqStr[1];
    
    // Convert file ('a'-'h') to index (0-7)
    if (fileChar < 'a' || fileChar > 'h') {
        std::cerr << "Invalid file character: " << fileChar << std::endl;
        return -1;
    }
    int fileIndex = fileChar - 'a';
    
    // Convert rank ('1'-'8') to index (0-7)
    if (rankChar < '1' || rankChar > '8') {
        std::cerr << "Invalid rank character: " << rankChar << std::endl;
        return -1;
    }
    int rankIndex = rankChar - '1';
    
    // Calculate square index
    int square = rankIndex * 8 + fileIndex;
    return square;
}