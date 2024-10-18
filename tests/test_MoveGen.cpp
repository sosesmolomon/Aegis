#nclude <gtest/gtest.h>
#include "../cpp-src/CBoard.h"
#include "../cpp-src/MoveList.h"
#include "../cpp-src/magic.h"

// Struct to hold test parameters
struct MoveGenTestParam {
    std::string fen;
    int expectedMoveCount;
};

// Test fixture
class MoveGenerationTest : public ::testing::TestWithParam<MoveGenTestParam> {};

TEST_P(MoveGenerationTest, CorrectMoveCount) {
    MoveGenTestParam param = GetParam();
    CBoard board = CBoard();
    CBoard *b = &board;
    board.generatePiecePossibleMoves();
    initMagic(&board);

    MoveList *generatedMoves = new MoveList();
    MoveList *gameHistory = new MoveList(); // If needed
    MoveList *legal_moves = new MoveList();
    
    b->loadFEN(param.fen, gameHistory);
    b->genAllMoves(generatedMoves, gameHistory, board.player);
    b->verifyLegalMoves(generatedMoves, gameHistory, board.player, legal_moves);

    EXPECT_EQ(legal_moves->size(), param.expectedMoveCount)
        << "Failed for FEN: " << param.fen;

    free(generatedMoves);
    free(gameHistory);
    free(legal_moves);
    // free(b);

}

// Instantiate the test suite with different FEN positions
INSTANTIATE_TEST_SUITE_P(
    MoveGeneration,
    MoveGenerationTest,
    ::testing::Values(
        MoveGenTestParam{"8/8/8/1pP5/8/8/8/K1k5 w - b6 0 1", 3}, // en passant
        MoveGenTestParam{"5rk1/8/8/8/8/8/8/4K2R w K - 0 1", 12}, // no castle through check
        MoveGenTestParam{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 20},// normal starting board
        MoveGenTestParam{"r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1", 26}, // legal castle both sides
        MoveGenTestParam{"7k/5Q2/6Q1/8/8/8/8/7K b - - 0 1", 0}, // black
        MoveGenTestParam{"7k/5Q2/8/8/8/8/7R/7K b - - 0 1", 0}, // checkmate
        MoveGenTestParam{"8/8/8/3pP3/8/8/8/4K1k1 w - d6 0 1", 5}, // en passant
        MoveGenTestParam{"8/8/8/5Pp1/8/8/8/4K1k1 w - g6 0 1", 5}, // en passant
        MoveGenTestParam{"8/8/8/pP6/8/8/8/4K2k w - a6 0 1", 7}, // en passant
        MoveGenTestParam{"8/8/3p4/4Pp2/8/8/8/4K1k1 w - f6 0 1", 6}, // en passant
        MoveGenTestParam{"k7/8/8/1pP5/8/8/8/4K3 w - b6 0 1", 7}, // en passant
        MoveGenTestParam{"2kr4/8/8/8/8/8/8/R3K3 w Q - 0 1", 13}, // no castle through check
        MoveGenTestParam{"k7/8/8/8/8/4q3/8/4K2R w K - 0 1", 2}, // no castle through check. rook can't move cause in check
        MoveGenTestParam{"k7/8/8/8/8/6n1/8/4K2R w K - 0 1", 12}, // no castle through check
        MoveGenTestParam{"k7/8/8/8/8/4b3/8/4K2R w K - 0 1", 12}, // no castle through check
        MoveGenTestParam{"5rk1/8/8/8/8/8/8/4K2R w K - 0 1", 12}, // no castle through check 
        MoveGenTestParam{"r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1", 26}, // legal castle both sides
        MoveGenTestParam{"2kq2r1/8/8/8/8/8/8/R3K2R w KQ - 0 1", 22}, // legal castle K
        MoveGenTestParam{"2kq4/8/8/8/8/8/8/4K2R w - - 0 1", 12}, // looks like legal castle K, but not
        MoveGenTestParam{"r3k1nr/8/8/8/8/8/8/R3K1NR w KQkq - 0 1", 26}, // legal castle both sides
        MoveGenTestParam{"r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1", 25}, // legal castle both side
        MoveGenTestParam{"8/8/8/2PpP3/8/8/8/k6K w - d6 0 1", 7}, // en_passant either side
        MoveGenTestParam{"4r3/8/8/3pP3/8/r7/4K3/k2r1r2 w - d6 0 1", 1}, // en_passant ONLY move
        MoveGenTestParam{"k5r1/b7/8/5B2/8/7n/5NPP/5RKN w - - 0 1", 1}, // reveal check checks. 1 move
        MoveGenTestParam{"rnb1kbnr/pppp1ppp/4p3/8/6Pq/5P2/PPPPP2P/RNBQKBNR w KQkq - 1 3", 0} // 0 moves, white in check mate
        // No trailing comma after the last argument
    )
);

