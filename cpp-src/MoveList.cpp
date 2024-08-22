#include "MoveList.h"
#include "print.h"

// Default constructor for moveStruct
moveStruct::moveStruct() : from(0), to(0), pT(0), pC(0) {}

// Parameterized constructor for moveStruct
moveStruct::moveStruct(int a, int b, int c, int d) : from(a), to(b), pT(c), pC(d) {}


moveStruct MoveList::at(int index) {
    return moves.at(index);
}

void MoveList::add(const moveStruct &move)
{
    moves.push_back(move);
}

void MoveList::clear()
{
    moves.clear();
}

void MoveList::sort()
{
    printf("sort the move list!");
}

void MoveList::init()
{
    printf("init the move list!");
}

// Remove a moveStruct at a specific index
void MoveList::remove(size_t index)
{
    if (index < moves.size())
    {
        moves.erase(moves.begin() + index);
    }
}

void MoveList::print()
{
    moveStruct curr;
    for (int i = 0; i < moves.size(); i++)
    {
        curr = moves.at(i);
        printf("{\n");
        printf("  from = %s\n", sqToStr[curr.from]);
        printf("  to =   %s\n", sqToStr[curr.to]);
        printf("  pT =   %s\n", pieceToStr[curr.pT]);
        printf("  pC =   %s\n", colorToStr[curr.pC]);
        printf("}\n");
    }
}
