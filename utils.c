#include "utils.h"

/*
PRINTS

h8

*/
int applyScalar(int** scalarArrays, uint64_t piece_bitboard, piece_type piece_type, color color)
{
    int sum = 0;
    int *scalar = (int*)malloc(64*sizeof(int));
    switch (piece_type)
    {
    case PAWN:
        scalar = scalarArrays[PAWN];
        break;
    case KNIGHT:
        scalar = scalarArrays[KNIGHT];
        break;
    case BISHOP:
        scalar = scalarArrays[BISHOP];
        break;
    case ROOK:
        scalar = scalarArrays[ROOK];
        break;
    case QUEEN:
        scalar = scalarArrays[QUEEN];
        break;
    case KING:
        scalar = scalarArrays[KING];
        break;
    }

    for (int i = 0; i < 64; i++)
    {
        if (piece_bitboard & (1ULL << i))
        {
            if (color == WHITE)
                sum += scalar[63 - i];
            else
                sum += scalar[i];
        }
    }
    return sum;
}

int evaluateBoard(Board *board, int** scalarArrays)
{
    int white_eval = 0, black_eval = 0, evaluation = 0;

    // if board.white_mated() return 1000
    // if board.black_mated() return -1000
    // if board.is_draw() return 0

    uint64_t white_pieces[] = {board->pawn_W, board->bishop_W, board->knight_W, board->rook_W, board->king_W, board->queen_W };
    uint64_t black_pieces[] = {board->pawn_B, board->bishop_B, board->knight_B, board->rook_B, board->king_B, board->queen_B};
    uint64_t value_multipliers[] = {1, 3, 3, 5, 9};
    piece_type pieces[NUM_PIECE_TYPES] = {PAWN, BISHOP, KNIGHT, ROOK, KING, QUEEN};

    printf("\n");
    for (int i = 0; i < 1; ++i)
    {
        // printf("num of pieces: %d", piece_count(white_pieces[i])); 
        black_eval -= (applyScalar(scalarArrays, black_pieces[i], pieces[i], BLACK) * value_multipliers[i]);
        white_eval += (applyScalar(scalarArrays, white_pieces[i], pieces[i], WHITE) * value_multipliers[i]);
    }

    evaluation = white_eval + black_eval;
    printf("\nWhites evaluation is: %d\nBlacks evaluation is: %d", white_eval, black_eval);
    printf("\nTotal evaluation: %d", evaluation);
    return evaluation;
}

int pieceCount(uint64_t board)
{
    int count = 0;

    for (int i = 63; i >= 0; --i)
    {
        if (((board >> i) & 1) == 1)
            count++;
        else
            continue;
    }
    return count;
}

void identifyPieceType(uint64_t square, Board *board)
{
    if ((square & board->pawn_W) >= 1)
        printf("\nwhite pawn");
    else if ((square & board->bishop_W) >= 1)
        printf("\nwhite bishop");
    else if ((square & board->knight_W) >= 1)
        printf("\nwhite knight");
    else if ((square & board->rook_W) >= 1)
        printf("\nwhite rook");
    else if ((square & board->queen_W) >= 1)
        printf("\nwhite queen");
    else if ((square & board->king_W) >= 1)
        printf("\nwhite king");
    else if ((square & board->pawn_B) >= 1)
        printf("\nblack pawn");
    else if ((square & board->bishop_B) >= 1)
        printf("\nblack bishop");
    else if ((square & board->knight_B) >= 1)
        printf("\nblack knight");
    else if ((square & board->rook_B) >= 1)
        printf("\nblack rook");
    else if ((square & board->queen_B) >= 1)
        printf("\nblack queen");
    else if ((square & board->king_B) >= 1)
        printf("\nblack king");
    else
        printf("x");
}

uint64_t fullBitBoard(Board *board)
{
    return board->pawn_W | board->bishop_W | board->knight_W | board->rook_W | board->queen_W | board->king_W | board->pawn_B | board->bishop_B | board->knight_B | board->rook_B | board->queen_B | board->king_B;
}


