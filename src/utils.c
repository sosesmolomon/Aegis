#include "utils.h"

/*
PRINTS

h8
*/
int applyScalar(int **scalarArrays, uint64_t piece_bitboard, piece_type piece_type, player_color color)
{
    int sum = 0;
    // int *scalar = (int*)malloc(64*sizeof(int));
    int *scalar;
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
    // free(scalar);
    return sum;
}

int evaluateBoard(Board *board, int **scalarArrays)
{
    int white_eval = 0, black_eval = 0, evaluation = 0;

    // if board.white_mated() return 1000
    // if board.black_mated() return -1000
    // if board.is_draw() return 0

    uint64_t white_pieces[] = {board->pawn_W, board->bishop_W, board->knight_W, board->rook_W, board->king_W, board->queen_W};
    uint64_t black_pieces[] = {board->pawn_B, board->bishop_B, board->knight_B, board->rook_B, board->king_B, board->queen_B};
    uint64_t value_multipliers[] = {1, 3, 3, 5, 1, 9}; // these might mean the engine only wants to move the queen first
    piece_type pieces[NUM_PIECE_TYPES] = {PAWN, BISHOP, KNIGHT, ROOK, KING, QUEEN};
    char piece_name[8][6] = {"PAWN", "BISHOP", "KNIGHT", "ROOK", "KING", "QUEEN"};

    printf("\n");
    for (int i = 0; i < 6; ++i)
    {
        // printf("num of pieces: %d", piece_count(white_pieces[i]));
        black_eval -= (applyScalar(scalarArrays, black_pieces[i], pieces[i], BLACK) * value_multipliers[i]);
        white_eval += (applyScalar(scalarArrays, white_pieces[i], pieces[i], WHITE) * value_multipliers[i]);

        printf("Whites %.*s bitboard: \n", (int)(sizeof(piece_name[i])), piece_name[i]);
        printBitString(white_pieces[i]);
        printf("\n");
        printf("Blacks%.*s bitboard:\n", (int)(sizeof(piece_name[i])), piece_name[i]);
        printBitString(black_pieces[i]);

        printf("\nWhites %.*s evaluation is: %d\nBlacks %.*s evaluation is: %d\n", (int)(sizeof(piece_name[i])), piece_name[i], white_eval, (int)(sizeof(piece_name[i])), piece_name[i], black_eval);
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
    }
    return count;
}
// should have tests: making sure a Pawn square (first check) isn't also any other kind of piece
piece_type identifyPieceType(uint64_t square, Board *board, player_color *color)
{
    if ((square & board->pawn_W) >= 1)
    {
        printf("white pawn");
        *color = WHITE;
        return PAWN;
    }
    else if ((square & board->bishop_W) >= 1)
    {
        *color = WHITE;
        return BISHOP;
    }
    else if ((square & board->knight_W) >= 1)
    {
        *color = WHITE;
        return KNIGHT;
    }
    else if ((square & board->rook_W) >= 1)
    {
        *color = WHITE;
        return ROOK;
    }
    else if ((square & board->queen_W) >= 1)
    {
        *color = WHITE;
        return QUEEN;
    }
    else if ((square & board->king_W) >= 1)
    {
        *color = WHITE;
        return KING;
    }
    else if ((square & board->pawn_B) >= 1)
    {
        *color = BLACK;
        return PAWN;
    }
    else if ((square & board->bishop_B) >= 1)
    {
        *color = BLACK;
        return BISHOP;
    }
    else if ((square & board->knight_B) >= 1)
    {
        *color = BLACK;
        return KNIGHT;
    }
    else if ((square & board->rook_B) >= 1)
    {
        *color = BLACK;
        return ROOK;
    }
    else if ((square & board->queen_B) >= 1)
    {
        *color = BLACK;
        return QUEEN;
    }
    else if ((square & board->king_B) >= 1)
    {
        *color = BLACK;
        return KING;
    }
    else
        return PAWN;
}

uint64_t fullBitBoard(Board *board)
{
    return board->pawn_W | board->bishop_W | board->knight_W | board->rook_W | board->queen_W | board->king_W | board->pawn_B | board->bishop_B | board->knight_B | board->rook_B | board->queen_B | board->king_B;
}
