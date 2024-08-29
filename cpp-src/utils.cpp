#include "utils.h"
#include "print.h"
#include <math.h>

#include "CBoard.h"

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
    int opp_color = oppColor(color);
    // need more here.
    // this is for checks.
    return  ( (1ULL << sq) & b->legalAttackedSquares[opp_color]) >= 1;
}

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

int firstOne(u64 b)
{
    // shift n times until there is a 1
    int n = 0;

    if (b)
    {
        while ((b & 1) == 0)
        {
            n++;
            b >>= 1;
        }
    }

    // clears the bottom bits somehow?
    // b = (b >> u64(n+1)) << u64(n+1);

    return n;
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
    if (abs(move.to - move.from) == 16 && move.pT == PAWN && move.pC == (player_color ^ WHITE) )
    {
        // opp pawn double moves and sits next to player pawn.     ensure looking at correct side of pawn
        if ((abs(getRow(move.to) - getRow(sq)) == 0) && ((getFile(move.to) - getFile(target)) == 0))
        {
            return true;
        }
    }
     return false;
}