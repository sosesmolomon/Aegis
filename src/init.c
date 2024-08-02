#include "init.h"

const char square_names[64][3] = {
    "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8",
    "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8",
    "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8",
    "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8",
    "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8",
    "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8",
    "g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8",
    "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8"};

// later: these should be weights that an ML model updates by playing a lot of games.
int pawnScalars[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6,
    7, 7, 7, 7, 7, 7, 7, 7};
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

    // a1 --> a8 --> h1 --> h8
    // white king: a5, white queen: a4
    //a1 == 1ULL << 63, a5 == 1ULL

    uint64_t mask = 1ULL << 48;
    board->pawn_W = mask ^ board->pawn_W;
    mask = 1ULL << (48 - 8);
    board->pawn_W = board->pawn_W | mask;

    // printBitString(board->pawn_B);

    // uint64_t full_board = fullBitBoard(board);
    // printBitString(full_board);
    return board;
}

Board *initTestBoards()
{
    Board *board = (Board *)malloc(sizeof(Board));
    // board->pawn_W = 0xFFUL << 48;
    // board->pawn_B = 0xFFUL << 8;

    // move white pawn and black pawn forward one for evaluation test
    // uint64_t mask = 1ULL << 55; //a2
    // board->pawn_W = mask ^ board->pawn_W;
    // mask = 1ULL << (55 - 8);
    // board->pawn_W = board->pawn_W | mask;

    board->knight_W = 1ULL << 56;

    // mask = 1ULL << 8; // h7
    // board->pawn_B = mask ^ board->pawn_B;
    // mask = 1ULL << (8+8);
    // board->pawn_B = board->pawn_B | mask;

    // printBitString(board->pawn_W);
    printBitString(fullBitBoard(board));
    return board;
}
