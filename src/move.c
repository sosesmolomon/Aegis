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
            printf("found something in square %d ", position);
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

void findBishopMoves() { return; }

void findKnightMoves() { return; }

void findRookMoves() { return; }

void findQueenMoves() { return; }

void findKingMoves() { return; }