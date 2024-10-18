#include <gtest/gtest.h>
#include "../cpp-src/CBoard.h"

TEST(CBoardTest, InitCBoard)
{
    CBoard board;
    board.initCBoard();

    EXPECT_EQ(board.pieceBB[PAWN], 0x00FF00000000FF00)
        << "PAWN bitboard does not match expected starting position.";
    EXPECT_EQ(board.pieceBB[BISHOP], 0b0010010000000000000000000000000000000000000000000000000000100100)
        << "BISHOP bitboard does not match expected starting position.";
    EXPECT_EQ(board.pieceBB[KNIGHT], 0b0100001000000000000000000000000000000000000000000000000001000010)
        << "KNIGHT bitboard does not match expected starting position.";
    EXPECT_EQ(board.pieceBB[ROOK], 0b1000000100000000000000000000000000000000000000000000000010000001)
        << "ROOK bitboard does not match expected starting position.";
    EXPECT_EQ(board.pieceBB[QUEEN], 0b000100000000000000000000000000000000000000000000000000000001000)
        << "QUEEN bitboard does not match expected starting position.";
    EXPECT_EQ(board.pieceBB[KING], 0b00001000000000000000000000000000000000000000000000000000000010000)
        << "KING bitboard does not match expected starting position.";
    EXPECT_EQ(board.coloredBB[BLACK], 0xFFFF000000000000)
        << "BLACK bitboard does not match expected starting position.";
    EXPECT_EQ(board.coloredBB[WHITE], 0x000000000000FFFF)
        << "WHITE bitboard does not match expected starting position.";
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
