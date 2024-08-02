#include "move.h"

bool pawnOnHomeRow(uint64_t pawnBB, player_color *curr_player)
{
    if (*curr_player == WHITE)
        return (pawnBB & white_pawn_home) >= 1 ? 1 : 0;
    else if (*curr_player == BLACK)
        return (pawnBB & black_pawn_home) >= 1 ? 1 : 0;
    else
    {
        fprintf(stderr, "Player color not found\n");
        exit(1);
    }
}

bool isEmptySquare(Board *board, int target)
{
    uint64_t mask = 1ULL << target;
    return ((mask & fullBitBoard(board)) >= 1) ? 0 : 1;
}

bool isLegalMove(Board *board, int target, player_color *curr_player)
{

    if (target >= 64 | target < 0)
        return false;

    uint64_t mask = 1ULL << target;

    // if enteringCheck() --> false

    if (isEmptySquare(board, target))
        return true;

    // if target square is same color as curr_player = illegal move
    if (*curr_player == WHITE)
        return ((whitePieces(board) & mask) >= 1) ? false : true;

    if (*curr_player == BLACK)
        return ((blackPieces(board) & mask) >= 1) ? false : true;

    fprintf(stderr, "Player color not found. in isLegalMove\n");
    exit(1);
}

int *findPawnMoves(Board *board, int *possible_moves, uint64_t pawnBB, player_color *curr_player, int position)
{
    // a pawn can always have, at most, 4 legal moves (1 forward, capture left/right, first move 2)
    int index = 0;
    int shift;

    // white pawn move = negative shift on position
    // black pawn move = positive shift on position

    if (pawnOnHomeRow(pawnBB, curr_player))
    {
        shift = (*curr_player == WHITE) ? -16 : 16;

        if (isEmptySquare(board, position + shift))
        {
            possible_moves[index] = shift;
            index++;
        }
        else
            printf("found something in square %d ", position + shift);
    }

    shift = (*curr_player == WHITE) ? -8 : 8;
    if (isEmptySquare(board, position + shift))
    {
        possible_moves[index] = shift;
        index++;
    }

    return possible_moves;
    // if on starting square()

    // column direction -- getColumn
    // if square not empty -- can't move

    // diagonals
    // if piece == other_color
    // canCapture()?
    // notEnteringCheck()?
}

int *findBishopMoves(Board *board, int *possible_moves, uint64_t knightBB, player_color *curr_player, int position)
{
    // 7, 9

    return possible_moves;
}

int horseMoves[] = {-17, -15, -10, -6, 6, 10, 15, 17};

bool isLegalKnightMove(int start, int end)
{
    int start_row, start_col, end_row, end_col, dX, dY;
    start_row = floor(start / 8);
    start_col = start % 8;

    end_row = floor(end / 8);
    end_col = end % 8;

    dX = abs(start_col - end_col);
    dY = abs(start_row - end_row);

    if ((dX == 1 && dY == 2) ^ (dX == 2 && dY == 1))
        return true;
    else
        return false;
}

// int horseMoves[] = {-17, -15, -10, -6, 6, 10, 15, 17};
int *findKnightMoves(Board *board, int *possible_moves, uint64_t knightBB, player_color *curr_player, int position)
{
    // i know starting position = 47

    // there are 4 legal moves (+6, +15, -10, -17). and 4 illegal moves.
    int shift;
    int target = position;
    int index = 0;
    for (int i = 0; i < 8; i++)
    {
        // -17
        shift = horseMoves[i];
        // printf("%d, ", shift);

        // 30 (good)
        target = position + shift;

        // printf("\ntarget = %d", target);
        if (isLegalKnightMove(position, target) && isLegalMove(board, target, curr_player))
        {
            possible_moves[index] = shift;
            index++;
        }
    }

    return possible_moves;
}

void findRookMoves() { return; }

void findQueenMoves() { return; }

void findKingMoves() { return; }
