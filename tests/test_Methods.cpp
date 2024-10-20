#include <gtest/gtest.h>
#include "../cpp-src/CBoard.h"
#include "../cpp-src/MoveList.h"
#include "../cpp-src/magic.h"
#include "../cpp-src/utils.h"

// Struct to hold test parameters
struct ChessMethodParam
{
    std::string fen;
    bool expectedIsInCheck; // is this isAttacked()?
    bool expectedIsInCheckmate;
    bool expectedIsInStalemate;
    bool expectedCanCastleShort;
    bool expectedCanCastleLong;
    // bool expectedCanEnPassant;
};

// Test fixture
class ChessMethodTest : public ::testing::TestWithParam<ChessMethodParam>
{
protected:
    CBoard *b;
    MoveList *game;
    MoveList *all_moves;
    MoveList *legal_moves;

    void SetUp() override
    {
        const ChessMethodParam &param = GetParam();

        b = new CBoard();
        game = new MoveList();
        all_moves = new MoveList();
        legal_moves = new MoveList();

        b->generatePiecePossibleMoves();
        initMagic(b);

        b->loadFEN(param.fen, game);
    }

    void TearDown() override
    {
        delete game;
        delete all_moves;
        delete legal_moves;
    }
};

TEST_P(ChessMethodTest, expectedIsInCheck)
{
    const ChessMethodParam &param = GetParam();
    EXPECT_EQ(b->isInCheck(b->player), param.expectedIsInCheck);
}
TEST_P(ChessMethodTest, expectedIsInCheckmate)
{
    const ChessMethodParam &param = GetParam();

    b->genAllMoves(all_moves, game);
    b->verifyLegalMoves(all_moves, game, legal_moves);

    EXPECT_EQ(b->isInCheckmate(legal_moves, b->player), param.expectedIsInCheckmate);
}

TEST_P(ChessMethodTest, expectedIsInStalemate)
{
    const ChessMethodParam &param = GetParam();

    b->genAllMoves(all_moves, game);
    b->verifyLegalMoves(all_moves, game, legal_moves);

    EXPECT_EQ(b->isInStalemate(legal_moves, b->player), param.expectedIsInStalemate);
}

TEST_P(ChessMethodTest, expectedCanCastleShort)
{
    const ChessMethodParam &param = GetParam();

    u64 king = b->pieceBB[KING] & b->coloredBB[b->player];
    int k_sq = firstOne(king);

    EXPECT_EQ(b->canCastleShort(k_sq, b->player), param.expectedCanCastleShort);
}

TEST_P(ChessMethodTest, expectedCanCastleLong)
{
    const ChessMethodParam &param = GetParam();

    u64 king = b->pieceBB[KING] & b->coloredBB[b->player];
    int k_sq = firstOne(king);

    EXPECT_EQ(b->canCastleLong(k_sq, b->player), param.expectedCanCastleLong);
}

// // only confirming that the LAST move in game-ml was a pawn double push
// TEST_P(ChessMethodTest, expectedCanEnPassant) {
//     const ChessMethodParam& param = GetParam();

//     b->genAllMoves(all_moves, game);
//     b->verifyLegalMoves(all_moves, game, legal_moves);

//     EXPECT_EQ(canEnPassant(game, ), param.expectedInCheck);

// }

// fen
// in check
// in checkmate
// in stalemate
// can castle short
// can castle long

INSTANTIATE_TEST_SUITE_P(
    ChessMethodTests,
    ChessMethodTest,
    ::testing::Values(
        ChessMethodParam{
            "8/8/8/1pP5/8/8/8/K1k5 w - b6 0 1", // fen
            false,                              // in check
            false,                              // in checkmate
            false,                              // in stalemate
            false,                              // can castle short
            false,                              // can castle long
        },

        ChessMethodParam{
            "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1",
            false, // in check
            false, // in checkmate
            false, // in stalemate
            true,  // can castle short
            true,  // can castle long
        },

        ChessMethodParam{
            "7k/5Q2/6Q1/8/8/8/8/7K b - - 0 1",
            false, // in check
            false, // in checkmate
            true,  // in stalemate
            false, // can castle short
            false, // can castle long
        },

        ChessMethodParam{
            "7k/5Q2/8/8/8/8/7R/7K b - - 0 1",
            true,  // in check
            true,  // in checkmate
            false, // in stalemate
            false, // can castle short
            false, // can castle long
        },

        ChessMethodParam{
            "2kr4/8/8/8/8/8/6n1/R3K3 w Q - 0 1",
            true,  // in check
            false, // in checkmate
            false, // in stalemate
            false, // can castle short
            false, // can castle long ,
        },
        ChessMethodParam{
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPpP/RNBQK2R w KQkq - 0 1",
            false,  // in check
            false, // in checkmate
            false, // in stalemate
            false, // can castle short
            false, // can castle long
        }));

/*
    "k7/8/8/8/8/4q3/8/4K2R w K - 0 1"
    "k7/8/8/8/8/6n1/8/4K2R w K - 0 1"
    "k7/8/8/8/8/4b3/8/4K2R w K - 0 1"
    "5rk1/8/8/8/8/8/8/4K2R w K - 0 1"
    "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"
    "2kq2r1/8/8/8/8/8/8/R3K2R w KQ - 0 1"
    "2kq4/8/8/8/8/8/8/4K2R w - - 0 1",
    "r3k1nr/8/8/8/8/8/8/R3K1NR w KQkq - 0 1"
    "r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1"
    "8/8/8/2PpP3/8/8/8/k6K w - d6 0 1"
    "4r3/8/8/3pP3/8/r7/4K3/k2r1r2 w - d6 0 1"
    "k5r1/b7/8/5B2/8/7n/5NPP/5RKN w - - 0 1"
    "rnb1kbnr/pppp1ppp/4p3/8/6Pq/5P2/PPPPP2P/RNBQKBNR w KQkq - 1 3"
*/