#include "init.h"

const char square_names[64][3] =
    {"h8", "g8", "f8", "e8", "d8", "c8", "b8", "a8",
     "h7", "g7", "f7", "e7", "d7", "c7", "b7", "a7",
     "h6", "g6", "f6", "e6", "d6", "c6", "b6", "a6",
     "h5", "g5", "f5", "e5", "d5", "c5", "b5", "a5",
     "h4", "g4", "f4", "e4", "d4", "c4", "b4", "a4",
     "h3", "g3", "f3", "e3", "d3", "c3", "b3", "a3",
     "h2", "g2", "f2", "e2", "d2", "c2", "b2", "a2",
     "h1", "g1", "f1", "e1", "d1", "c1", "b1", "a1"};

// later: these should be weights that an ML model updates by playing a lot of games.
int pawnScalars[64] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7};
int bishopScalars[64] = {
    3, 1, 1, 1, 1, 1, 1, 3,
    1, 3, 1, 1, 1, 1, 3, 1,
    1, 1, 3, 1, 1, 3, 1, 1,
    1, 2, 1, 3, 3, 1, 2, 1,
    2, 1, 2, 3, 3, 2, 1, 2,
    1, 2, 3, 1, 1, 3, 2, 1,
    1, 3, 1, 1, 1, 1, 3, 1,
    3, 1, 1, 1, 1, 1, 1, 3};
int knightScalars[64] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 2, 2, 2, 2, 2, 2, 1,
    1, 2, 3, 3, 3, 3, 2, 1,
    1, 2, 3, 4, 4, 3, 2, 1,
    1, 2, 3, 4, 4, 3, 2, 1,
    1, 2, 3, 3, 3, 3, 2, 1,
    1, 2, 2, 2, 2, 2, 2, 1,
    1, 1, 1, 1, 1, 1, 1, 1};
int rookScalars[64] = {
    1, 1, 1, 3, 3, 1, 1, 1,
    1, 1, 1, 3, 3, 1, 1, 1,
    1, 1, 1, 2, 2, 1, 1, 1,
    1, 1, 1, 2, 2, 1, 1, 1,
    1, 1, 1, 2, 2, 1, 1, 1,
    1, 1, 1, 2, 2, 1, 1, 1,
    2, 5, 5, 5, 5, 5, 5, 2,
    1, 1, 1, 1, 1, 1, 1, 1};
int queenScalars[64] = {
    2, 2, 2, 3, 3, 2, 2, 2,
    2, 3, 3, 3, 3, 3, 3, 2,
    2, 3, 4, 4, 4, 4, 3, 2,
    3, 3, 4, 5, 5, 4, 3, 3,
    3, 3, 4, 5, 5, 4, 3, 3,
    2, 3, 4, 4, 4, 4, 3, 2,
    2, 3, 3, 3, 3, 3, 3, 2,
    2, 2, 2, 3, 3, 2, 2, 2};
int kingScalars[64] = {
    4, 3, 2, 1, 1, 2, 3, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0};

// Function to initialize the array of pointers
int **initScalarArrayPointers()
{
    int **scalarArrays = (int **)malloc(NUM_PIECE_TYPES * sizeof(int *));
    if (scalarArrays == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1); // Exit if malloc fails
    }
    scalarArrays[PAWN] = pawnScalars;
    scalarArrays[KNIGHT] = knightScalars;
    scalarArrays[BISHOP] = bishopScalars;
    scalarArrays[ROOK] = rookScalars;
    scalarArrays[QUEEN] = queenScalars;
    scalarArrays[KING] = kingScalars;

    return scalarArrays;
}

Board *initBitBoards()
{
    white_pawn_home = 0xFFUL << 48;
    black_pawn_home = 0xFFUL << 8;

    Board *board = (Board *)malloc(sizeof(Board));
    board->pawn_W = 0xFFUL << 48;
    board->bishop_W = (1ULL << 61) | (1ULL << 58);
    board->knight_W = (1ULL << 62) | (1ULL << 57);
    board->rook_W = (1ULL << 63) | (1ULL << 56);
    board->queen_W = 1ULL << 60;
    board->king_W = 1ULL << 59;

    board->pawn_B = 0xFFUL << 8; // takes 0b0000000000000000000000000000000000000000000000000000000011111111 --> 0b0000000000000000000000000000000000000000000000001111111100000000
    board->bishop_B = (1ULL << 2) | (1ULL << 5);
    board->knight_B = (1ULL << 1) | (1ULL << 6);
    board->rook_B = (1ULL << 0) | (1ULL << 7);
    board->queen_B = 1ULL << 4;
    board->king_B = 1ULL << 3;

    return board;
}

Board *initTestBoards()
{
    Board *board = (Board *)malloc(sizeof(Board));

    board->pawn_W = 0xFFUL << 48;
    // board->bishop_W = (1ULL << 61) | (1ULL << 58);
    // board->knight_W = (1ULL << 62) | (1ULL << 57);
    // board->rook_W = (1ULL << 63) | (1ULL << 56);
    // board->queen_W = 1ULL << 60;
    board->king_W = 1ULL << 59;

    // board->pawn_B = 0xFFUL << 8; // takes 0b0000000000000000000000000000000000000000000000000000000011111111 --> 0b0000000000000000000000000000000000000000000000001111111100000000
    // board->bishop_B = (1ULL << 47);
    // board->knight_B = (1ULL << 1) | (1ULL << 6);
    // board->rook_B = (1ULL << 0) | (1ULL << 7);
    board->rook_B = 1ULL << 3;
    // board->king_B = 1ULL << 3;
    return board;
}
