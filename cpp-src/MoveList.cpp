#include "MoveList.h"
#include "print.h"

// Default constructor for moveStruct
moveStruct::moveStruct() : from(0), to(0), pT(0), pC(0) {}

// Parameterized constructor for moveStruct
moveStruct::moveStruct(int from, int to, int pT, int pC, int isCapture, int isEnPassant, int isCastling ) : from(from), to(to), pT(pT), pC(pC), isCapture(isCapture), isEnPassant(isEnPassant), isCastling(isCastling)  {}

moveStruct MoveList::at(int index)
{
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
    this->curr_idx = 0;
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
        printf("  isCapture = %d", curr.isCapture);
        printf("  isEnPassant = %d", curr.isEnPassant);
        printf("  isCastling = %d", curr.isCastling);
        printf("}\n");
    }
}

size_t MoveList::size() {
    return this->moves.size();
}
