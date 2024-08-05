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
    case NONE:
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

void findMoves(Board *board, piece_type curr_piece, player_color *curr_player, int position, bool doPrint)
{

    pawn_moves = (int *)malloc(sizeof(int) * 4);
    bishop_moves = (int *)malloc(sizeof(int) * 28);
    knight_moves = (int *)malloc(sizeof(int) * 8);
    rook_moves = (int *)malloc(sizeof(int) * 28);
    queen_moves = (int *)malloc(sizeof(int) * 56);
    king_moves = (int *)malloc(sizeof(int) * 8);

    switch (curr_piece)
    {
    case NONE:
        break;
    case PAWN:
        pawn_moves = findPawnMoves(board, pawn_moves, curr_player, position);
        if (!doPrint)
            break;
        printf("\n");
        printf("Possible moves for Pawn at position %d: ", position);
        for (int j = 0; j < 4; j++)
            printf("%d, ", pawn_moves[j]);
        printf("\n");
        printPossibleMoves(pawn_moves, position);
        break;
    case BISHOP:
        bishop_moves = findBishopMoves(board, bishop_moves, curr_player, position);
        if (!doPrint)
            break;
        printf("\n");
        printf("Possible moves for Bishop at position %d: ", position);
        for (int j = 0; j < 28; j++)
            printf("%d, ", bishop_moves[j]);
        printf("\n");

        printPossibleMoves(bishop_moves, position);
        break;
    case KNIGHT:
        knight_moves = findKnightMoves(board, knight_moves, curr_player, position);
        if (!doPrint)
            break;
        printf("\n");
        printf("Possible moves for Knight at position %d: ", position);
        for (int j = 0; j < 8; j++)
        {
            printf("%d, ", knight_moves[j]);
        }
        printf("\n");
        printPossibleMoves(knight_moves, position);
        break;
    case ROOK:
        rook_moves = findRookMoves(board, rook_moves, curr_player, position);
        if (!doPrint)
            break;
        printf("\n");
        printf("Possible moves for Rook at position %d: ", position);
        for (int j = 0; j < 28; j++)
        {
            printf("%d, ", rook_moves[j]);
        }
        printf("\n");
        printPossibleMoves(rook_moves, position);
        break;
    case QUEEN:
        queen_moves = findQueenMoves(board, queen_moves, curr_player, position);
        if (!doPrint)
            break;
        printf("\n");
        printf("Possible moves for Queen at position %d: ", position);
        for (int j = 0; j < 56; j++)
            printf("%d, ", queen_moves[j]);
        printf("\n");
        printPossibleMoves(queen_moves, position);
        break;
    case KING:
        king_moves = findKingMoves(board, king_moves, curr_player, position);
        if (!doPrint)
            break;
        printf("\n");
        printf("Possible moves for King at position %d: ", position);
        for (int j = 0; j < 8; j++)
        {
            printf("%d, ", king_moves[j]);
        }
        printf("\n");
        printPossibleMoves(king_moves, position);
        break;
    default:
        break;
    }
}

// should have tests: making sure a Pawn square (first check) isn't also any other kind of piece
piece_type identifyPieceType(uint64_t square, Board *board, player_color *color)
{
    if ((square & board->pawn_W) >= 1)
    {
        // printf("\npawn_W & square: \n");
        // printBitString(board->pawn_W & square);
        // printf("white pawn\n");
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
    {
        // printf("NONE\n");
        return NONE;
    }
}

uint64_t fullBitBoard(Board *board)
{
    return board->pawn_W | board->bishop_W | board->knight_W | board->rook_W | board->queen_W | board->king_W | board->pawn_B | board->bishop_B | board->knight_B | board->rook_B | board->queen_B | board->king_B;
}

uint64_t whitePieces(Board *board)
{
    return board->pawn_W | board->bishop_W | board->knight_W | board->rook_W | board->queen_W | board->king_W;
}
uint64_t blackPieces(Board *board)
{
    return board->pawn_B | board->bishop_B | board->knight_B | board->rook_B | board->queen_B | board->king_B;
}
