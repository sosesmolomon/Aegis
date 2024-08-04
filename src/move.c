#include "move.h"

bool pawnOnHomeRow(player_color *curr_player, int position)
{
    uint64_t pawnBB = 1ULL << position;

    //testing
    // printf("\n");
    // printBitString(pawnBB);
    // printf("\n");
    // printBitString(white_pawn_home);
    // printf("\n");
    // printf("%llu", pawnBB & white_pawn_home);


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

    if (!isEmptySquare(board, target))
        return false;

    // if target square is same color as curr_player = illegal move
    if (*curr_player == WHITE)
        return ((whitePieces(board) & mask) >= 1) ? false : true;

    if (*curr_player == BLACK)
        return ((blackPieces(board) & mask) >= 1) ? false : true;

    fprintf(stderr, "Player color not found. in isLegalMove\n");
    exit(1);
}

int *findPawnMoves(Board *board, int *possible_moves, player_color *curr_player, int position)
{
    // a pawn can always have, at most, 4 legal moves (1 forward, capture left/right, first move 2)
    int index = 0;
    int shift;

    // white pawn move = negative shift on position
    // black pawn move = positive shift on position

    if (pawnOnHomeRow(curr_player, position))
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

bool isLegalBishopMove(int start, int end)
{
    int start_row, start_col, end_row, end_col, dX, dY;
    start_row = floor(start / 8);
    start_col = start % 8;

    end_row = floor(end / 8);
    end_col = end % 8;

    dX = abs(start_col - end_col);
    dY = abs(start_row - end_row);

    if (dX == dY)
        return true;
    else
        return false;
}
int bishopMoves[4][7] = {{7, 14, 21, 28, 35, 42, 49}, {-7, -14, -21, -28, -35, -42, -49}, {9, 18, 27, 36, 45, 54, 63}, {-9, -18, -27, -36, -45, -54, -63}};

int *findBishopMoves(Board *board, int *possible_moves, player_color *curr_player, int position)
{
    int shift;
    int target = position;
    int index = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            shift = bishopMoves[i][j];
            target = position + shift;

            // printf("\ntarget = %d", target);
            if (isLegalBishopMove(position, target) && isLegalMove(board, target, curr_player))
            {
                possible_moves[index] = shift;
                index++;
            }
            // end this route
            else
                break;
        }
    }

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
int *findKnightMoves(Board *board, int *possible_moves, player_color *curr_player, int position)
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

bool isLegalRookMove(int start, int end)
{
    int start_row, start_col, end_row, end_col, dX, dY;
    start_row = floor(start / 8);
    start_col = start % 8;

    end_row = floor(end / 8);
    end_col = end % 8;

    dX = abs(start_col - end_col);
    dY = abs(start_row - end_row);

    if ((dX >= 1 && dY == 0) || (dX == 0 && dY >= 1) || ((dX % 8 == 0) && dY == 0) || (dX == 0 && (dY % 8 == 0)))
        return true;
    else
        return false;
}

int rookMoves[4][7] = {{1, 2, 3, 4, 5, 6, 7}, {-1, -2, -3, -4, -5, -6, -7}, {8, 16, 24, 32, 40, 48, 56}, {-8, -16, -24, -32, -40, -48, -56}};
int *findRookMoves(Board *board, int *possible_moves, player_color *curr_player, int position)
{
    int shift;
    int target = position;
    int index = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            shift = rookMoves[i][j];
            target = position + shift;

            // printf("\ntarget = %d", target);
            if (isLegalRookMove(position, target) && isLegalMove(board, target, curr_player))
            {
                possible_moves[index] = shift;
                index++;
            }
            // end this route
            else
                break;
        }
    }
    return possible_moves;
}

int *findQueenMoves(Board *board, int *possible_moves, player_color *curr_player, int position)
{
    int shift;
    int target = position;
    int index = 0;

    for (int i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 7; j++)
        {
            shift = rookMoves[i][j];
            target = position + shift;

            if (isLegalRookMove(position, target) && isLegalMove(board, target, curr_player))
            {
                possible_moves[index] = shift;
                index++;
            }
            // end this route
            else
                break;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            shift = bishopMoves[i][j];
            target = position + shift;

            // printf("\ntarget = %d", target);
            if (isLegalBishopMove(position, target) && isLegalMove(board, target, curr_player))
            {
                possible_moves[index] = shift;
                index++;
            }
            // end this route
            else
                break;
        }
    }

    return possible_moves;
}

int kingMoves[] = {1, -1, 8, -8, 9, -9, 7, -7};
int *findKingMoves(Board *board, int *possible_moves, player_color *curr_player, int position)
{
    //todo: look for castle opportunity

    int shift;
    int index = 0;
    int target = position;

    for (int i = 0; i < 8; i++)
    {
        shift = kingMoves[i];
        target = position + shift;

        if ((isLegalBishopMove(position, target) || isLegalRookMove(position, target)) && isLegalMove(board, target, curr_player))
        {
            possible_moves[index] = shift;
            index++;
        }
    }

    return possible_moves;
}
