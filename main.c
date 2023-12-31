#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typedefs.h"

int pawn_value = 10;
int knight_value = 30;
int bishop_value = 30;
int rook_value = 50;
int queen_value = 90;

char SQUARE_NAMES[64][3] = {
        "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
        "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
        "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
        "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
        "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
        "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
        "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
        "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
};


void printBitboard(Bitboard board) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            int index = row * 8 + col;
            int bit = (board >> index) & 1;

            printf("%s ", SQUARE_NAMES[index]);

            //pirintf("%d ", bit);
        }
        printf("\n");
    }
}


void assemble_bitboards() {
    board.pawn_W = 0xFFUL << 48;
    bishop_W = (1UL << 61) | (1UL << 58);
    knight_W = (1UL << 62) | (1UL << 57);
    rook_W = (1UL << 63) | (1UL << 56);
    queen_W = 1UL << 59;
    king_W = 1UL << 60;


    pawn_B = 0xFFUL << 8;
    bishop_B = (1UL << 2) | (1UL << 5);
    knight_B = (1UL << 1) | (1UL << 6);
    rook_B = (1UL << 0) | (1UL << 7);
    queen_B = 1UL << 3;
    king_B = 1UL << 4;

    // Bitboard full_board = white_pawns | white_knights | white_queens | white_rooks | white_bishops | white_king | black_bishops | black_king | black_knights | black_pawns | black_queens | black_rooks; 

    // Print the bitboard
    // printBitboard(full_board);
}

int piece_count(Bitboard board) {
    int count = 0;

    for (int i=63; i>=0; --i) {
        if ((board >> i) & 1 == 1) count++;
        else continue;
    }
    return count;
    }


// TODO: create adjustment multiplier boards to evaluate positions 
/*
void adjust_evaluations() {
    // board = h1 g1 f1 ... a1 h2 g2 ... c8 b8 a8

    
    int white_pawn_adj[] = {
        10, 10, 10, 10, 10, 10, 10, 10,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    int white_pawn_adj[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    int white_pawn_adj[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    int white_pawn_adj[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

}
*/

int evaluate_board() {
    int evaluation = 0;

    Board board = {};

    // if board.white_mated() return 1000
    // if board.black_mated() return -1000
    // if board.is_draw() return 0

    Bitboard white_pieces[] = {board.pawn_W, board.knight_W, board.bishop_W, rook_W, queen_W};
    Bitboard black_pieces[] = {pawn_B, knight_B, bishop_B, rook_B, queen_B};
    Bitboard value_multipliers[] = {10, 30, 30, 50, 90};

    printBitboard(white_pieces[0]);
    printf("\n");
    printBitboard(king_W);
    printf("\n");
    for (int i=0; i<5; ++i) {
        evaluation += (piece_count(white_pieces[i]) * value_multipliers[i]);
        //evaluation -= (piece_count(black_pieces[i]) * value_multipliers[i]);
    }

    return evaluation;
}

int main()
{
    
    assemble_bitboards();


    printf("%d", evaluate_board());
    return 0;
}