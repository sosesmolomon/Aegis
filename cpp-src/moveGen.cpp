#include "CBoard.h"
#include "utils.h"
#include "print.h"
#include "magic.h"
#include "MoveList.h"

void CBoard::genAllMoves(MoveList *ml)
{
    u64 attacked = 0ULL;
    u64 targetBB = this->coloredBB[this->player] ^ UINT64_MAX; 

//     this->genPawnMoves(ml, targetBB);
//     this->genBishopMoves(ml, targetBB);
//     this->genKnightMoves(ml, targetBB);
//     this->genRookMoves(ml, targetBB);
//     this->genQueenMoves(ml, targetBB);
}

void CBoard::fillAttackBBs(u64 targetBB) {
    // captures 
    // u64 targetBB = this->fullBoard() & this->coloredBB[this->player^WHITE];

    // all moves
    // u64 targetBB = UINT64_MAX;

    // quiet moves
    // u64 targetBB = ( UINT64_MAX ^ this->fullBoard() );

    this->genPawnAttacks(targetBB);
    this->genBishopAttacks(targetBB);
    this->genKnightAttacks(targetBB);
    this->genRookAttacks(targetBB);
    this->genQueenAttacks(targetBB);
    this->genKingAttacks(targetBB);
}

void CBoard::genPawnMoves(MoveList *ml, u64 targetBB) {}


void genPawnAttacksW();
void genPawnAttacksB();

void CBoard::genPawnAttacks(u64 targetBB) {
    int color = this->player;

    u64 allBB = this->pieceBB[PAWN] & this->coloredBB[color];
    
    u64 toBB = 0ULL;

     for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        
    } 
    this->pieceAttacks[color][BISHOP] = toBB;

    
}

void CBoard::genBishopMoves(MoveList *ml, u64 targetBB) {}

void CBoard::genBishopAttacks(u64 targetBB) {

    int color = this->player;
    u64 allBB = this->pieceBB[BISHOP] & this->coloredBB[color];
    
    u64 toBB = 0ULL;

     for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        toBB |= (getBishopAttacks(fr, this->fullBoard()) & targetBB);
    } 
    this->pieceAttacks[color][BISHOP] = toBB;

}
// generate quiet moves, captures, all moves, based on targetBB;
void CBoard::genKnightMoves(MoveList *ml, u64 targetBB) {
    int color = this->player;

    u64 allBB = this->pieceBB[KNIGHT] & this->coloredBB[color];
    u64 toBB;

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        toBB |= this->knightPosAttacks[fr] & targetBB;
        for (int to = firstOne(toBB); to != 64; to = firstOne(toBB)) {
            // add move
            // ml->add(moveStruct(fr, to, KNIGHT, color));/
        }
    }
}

// use this as new move generation -- pass emptyBB or opp_colorBB for moves/attacks
void CBoard::genKnightAttacks(u64 targetBB)
{
    int color = this->player;

    u64 allBB = this->pieceBB[KNIGHT] & this->coloredBB[color];
    u64 toBB = 0ULL;

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        toBB |= this->knightPosAttacks[fr] & targetBB;
    }
    this->pieceAttacks[color][KNIGHT] = toBB;
}

void CBoard::genRookAttacks(u64 targetBB) {
    int color = this->player;

    u64 allBB = this->pieceBB[ROOK] & this->coloredBB[color];
    u64 toBB = 0ULL;

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        toBB |= ( getRookAttacks(fr, this->fullBoard()) & targetBB );
    }
    this->pieceAttacks[color][ROOK] = toBB;
}

void CBoard::genQueenAttacks(u64 targetBB) {
    int color = this->player;

    u64 allBB = this->pieceBB[QUEEN] & this->coloredBB[color];
    u64 toBB = 0ULL;

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        toBB |= ( getRookAttacks(fr, this->fullBoard()) & targetBB ); 
        toBB |= ( getBishopAttacks(fr, this->fullBoard()) & targetBB ); 
        
    }
    this->pieceAttacks[color][QUEEN] = toBB;
}

void CBoard::genKingAttacks(u64 targetBB) {
    int color = this->player;

    u64 allBB = this->pieceBB[KING] & this->coloredBB[color];
    u64 toBB = 0ULL;

    for (int fr = firstOne(allBB); fr != 64; fr = firstOne(allBB))
    {
        toBB |= this->kingPosAttacks[fr] & targetBB;  
        
    }
    this->pieceAttacks[color][KING] = toBB;
}

bool CBoard::isAttacked(int to, int color) {
    //pawn attacking square

    if ( (this->knightPosAttacks[to] & this->pieceBB[KNIGHT] & this->coloredBB[color] ) != 0){
        return true;
    }
    if ( (getBishopAttacks(to, this->fullBoard())& ( this->pieceBB[BISHOP] | this->pieceBB[QUEEN] ) & this->coloredBB[color]) != 0 ) {
        return true;
    }

    if ( (getRookAttacks(to, this->fullBoard())) & (this -> pieceBB[ROOK] | this->pieceBB[QUEEN] ) & this->coloredBB[color] != 0) {
        return true;
    }

    if ( (this->kingPosAttacks[to] & this->pieceBB[KING] & this->coloredBB[color] ) != 0) {
        return true;
    }
    return false;
}

