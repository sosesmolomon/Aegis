#ifndef MOVE_LIST_H
#define MOVE_LIST_H

#include <vector>

typedef struct moveStruct
{
    int from;
    int to;
    int pT;
    int pC;
    
    // Constructors
    moveStruct();
    moveStruct(int a, int b, int c, int d);

} moveStruct;

class MoveList
{
    std::vector<moveStruct> moves;

public:
    void init();
    void clear();
    void sort();
    void remove(size_t index);
    void add(const moveStruct &move);
    void print();
};

#endif