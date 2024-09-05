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

    // isCapture?

    // maybe store some special identifier for en passant...
    // if MoveList.at(index-1).isEnPassant == 1
    // then pawn captures diagonally is legal.

    // Constructors
    moveStruct();
    moveStruct(int from, int to, int pT, int pC, int isCapture = 0, int isEnPassant = 0, int isCastlingShort = 0, int isCastlingLong = 0);
    

} moveStruct;

class MoveList
{
    std::vector<moveStruct> moves;

public:
    int curr_idx;
    moveStruct at(int index);
    void init();
    void clear();
    void sort();
    void remove(size_t index);
    void add(const moveStruct &move);
    void print(int index = -1);
    size_t size();
};

#endif