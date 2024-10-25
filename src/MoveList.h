#ifndef MOVE_LIST_H
#define MOVE_LIST_H

#include <vector>


typedef struct moveStruct
{
    int from;
    int to;
    int pT;
    int pC;
    bool isCapture;
    bool isEnPassant;
    bool isCastlingShort;
    bool isCastlingLong;
    int capturedP; // get rid of this, maybe need identifyCapturedPiece() for undoMove()
    int promotion;
    float eval;
    bool isFirstPieceMove;
    void toString();

    // isCapture?

    // maybe store some special identifier for en passant...
    // if MoveList.at(index-1).isEnPassant == 1
    // then pawn captures diagonally is legal.

    // Constructors
    moveStruct();
    moveStruct(int from, int to, int pT, int pC, int isCapture = 0, int isEnPassant = 0, int isCastlingShort = 0, int isCastlingLong = 0, int capturedP = 6, int promotion = 6, float eval = 0.0, bool isFirstPieceMove = false /* int for empty*/);


} moveStruct;

class MoveList
{
    std::vector<moveStruct> moves;
public:
    int curr_idx;
    moveStruct at(int index);
    void init();
    void clear();
    void sort(); // need this! sort based on eval? yes.
    void remove(size_t index);
    void add(const moveStruct &move);
    void print(int index = -1);
    size_t size();
};

#endif