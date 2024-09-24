#ifndef CBOARD_H
#define CBOARD_H

#include <stdint.h>
#include "bitboard.h"
#include "MoveList.h"

typedef uint64_t u64;

const int nPieceT = 6;
const int nPieceC = 12;

// a1 = 0
// h8 = 63
enum enumSquare
{
    a1,
    b1,
    c1,
    d1,
    e1,
    f1,
    g1,
    h1,
    a2,
    b2,
    c2,
    d2,
    e2,
    f2,
    g2,
    h2,
    a3,
    b3,
    c3,
    d3,
    e3,
    f3,
    g3,
    h3,
    a4,
    b4,
    c4,
    d4,
    e4,
    f4,
    g4,
    h4,
    a5,
    b5,
    c5,
    d5,
    e5,
    f5,
    g5,
    h5,
    a6,
    b6,
    c6,
    d6,
    e6,
    f6,
    g6,
    h6,
    a7,
    b7,
    c7,
    d7,
    e7,
    f7,
    g7,
    h7,
    a8,
    b8,
    c8,
    d8,
    e8,
    f8,
    g8,
    h8
};

// u64 *lookup_u64;

class CBoard
{
public:
    bool inCheck[2];
    bool atHomeCastleShort[2];
    bool atHomeCastleLong[2];

    bool inCheckmate[2];

    bool player;
    // problem with this is I need to call each of these individually. It would be better if I could call BB[WHITE + KNIGHT] -- BB [1+3]
    Bitboard pieceBB[nPieceT + 1]; // empty board
    Bitboard coloredBB[2];

    u64 white_pawn_home;
    u64 black_pawn_home;
    u64 pieceHomes;

    Bitboard legalAttackedSquares[2];

    // these are all generating correctly!

    u64 posAttackBBs[nPieceT][64];
    u64 pawnPosAttacks[2][64];
    u64 pawnPosPushes[2][64];
    u64 bishopPosAttacks[64];
    u64 knightPosAttacks[64];
    u64 rookPosAttacks[64];
    u64 queenPosAttacks[64];
    u64 kingPosAttacks[64];

    u64 pieceAttacks[2][nPieceT];

    u64 fullBoard();
    u64 emptyBoard();

    void initCBoard();
    void initTestBoard();

    void generatePawnPossibleMoves();

    bool isLegalBishopMove(int start, int end);
    void generateBishopPossibleMoves();

    bool isLegalKnightMove(int start, int end);
    void generateKnightPossibleMoves();

    bool isLegalRookMove(int start, int end);
    void generateRookPossibleMoves();

    // bool isLegalQueenMove(int start, int end);
    void generateQueenPossibleMoves();

    bool isLegalKingMove(int start, int end);
    void generateKingPossibleMoves();

    void generatePiecePossibleMoves();
    // void removeAttackEdges();

    void genAllLegalMoves(MoveList *ml, MoveList *game_ml, int color, bool onlyAttacks);

    // TODO
        // separate attack square generation and moveList generation
    void genLegalPawnMoves(MoveList *ml, MoveList *game_ml, int opp_color, bool onlyAttacks);
    void genLegalBishopMoves(MoveList *ml, MoveList *game_ml, int opp_color, bool onlyAttacks);
    void genLegalKnightMoves(MoveList *ml, MoveList *game_ml, int opp_color, bool onlyAttacks);
    void genLegalRookMoves(MoveList *ml, MoveList *game_ml, int opp_color, bool onlyAttacks);
    void genLegalQueenMoves(MoveList *ml, MoveList *game_ml, int opp_color, bool onlyAttacks);
    void genLegalKingMoves(MoveList *ml, MoveList *game_ml, int opp_color, bool onlyAttacks);

    bool canCastleShort(int sq, int color);
    bool canCastleLong(int sq, int color);

    void setSq(int pT, int pC, int sq);

    void verifyLegalMoves(MoveList *ml, MoveList *game, int color, MoveList *legal_moves);

    bool isInCheck(int color);
    bool isInCheckmate(MoveList *legals, int color);


    // gen all moves? or attacks? well. attacks are if targetBB == opp_color

    void genAllMoves(MoveList *ml, MoveList *game, int color);
    void genQuietMoves(MoveList *ml, MoveList *game, int color);
    void genCaptureMoves(MoveList *ml, MoveList *game, int color);

    void fillAttackBBs(MoveList *game, u64 targetBB, int color);

    void genPawnMoves(MoveList *ml, MoveList *game, u64 targetBB, int color);
    void genPawnPushes(MoveList *ml, int color, int from);
    void genPawnDiags(MoveList *ml, MoveList *game, int color, int from);
    void genPawnPromotions(MoveList *ml, int color, int from);
    void genPawnAttacks(MoveList *game, u64 targetBB, int color);

    void genBishopMoves(MoveList *ml, u64 targetBB, int color);
    void genBishopAttacks(u64 targetBB, int color);

    void genKnightMoves(MoveList *ml, u64 targetBB, int color);
    void genKnightAttacks(u64 targetBB, int color);

    void genRookMoves(MoveList *ml, u64 targetBB, int color);
    void genRookAttacks(u64 targetBB, int color);

    void genQueenMoves(MoveList *ml, u64 targetBB, int color);
    void genQueenAttacks(u64 targetBB, int color);
    
    void genKingMoves(MoveList *ml, MoveList *game, u64 targetBB, int color);
    void genKingAttacks(u64 targetBB, int color);

    bool isAttacked(int to, int color);
    
};

enum pieceT
{
    PAWN,   // 0
    BISHOP, // 1
    KNIGHT, // 2
    ROOK,
    QUEEN,
    KING, // 5
    empty
};

// black = 0
// white = 1
enum pieceC
{
    BLACK,
    WHITE
};

#endif