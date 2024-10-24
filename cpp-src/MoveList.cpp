#include "MoveList.h"
#include "print.h"

// Default constructor for moveStruct
moveStruct::moveStruct() : from(0), to(0), pT(0), pC(0) {}

// Parameterized constructor for moveStruct
moveStruct::moveStruct(int from, int to, int pT, int pC, int isCapture, int isEnPassant, int isCastlingShort, int isCastlingLong, int capturedP, bool isPromotion, float eval) : from(from), to(to), pT(pT), pC(pC), isCapture(isCapture), isEnPassant(isEnPassant), isCastlingShort(isCastlingShort), isCastlingLong(isCastlingLong), capturedP(capturedP), isPromotion(isPromotion), eval(eval) {}

char const pieceLtoStr[2][7] = {
    {'p', 'b', 'n', 'r','q','k'},
    {'P', 'B','N','R','Q','K'}
};

void moveStruct::toString() {
    // Captures
    // Bxe5 -- bishop captures on e5


    // Disambiguated moves
    // when two of the same piece can move to the same square, need to identify: Rdf8 (rook on d8 moves to f8)


    printf("%c ", pieceLtoStr[this->pC][this->pT]);
    printf("%c%d%c%d", files[this->from % 8], (int)(floor( (this->from) / 8 ) + 1), files[this->to % 8], (int)(floor( (this->to) / 8 ) + 1));

    // if (this->isCapture)
}

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

void MoveList::print(int index)
{
    if (moves.size() < 1)
    {
        printf("no moves to print\n");
        return;
    }
    // if index = -1, print the whole thing
    int i, end;
    if (index == -1 || index >= moves.size())
    {
        index = 0; // for the for loop
        end = moves.size();
    }
    else
    {
        i = index; // for printing
        end = index + 1;
    }
    printf("iterating from %d to %d\n", index, end);

    moveStruct curr;
    for (i = index; i < end; i++)
    {
        curr = moves.at(i);
        printf("{               index = %d\n", i);
        printf("  from = %s\n", sqToStr[curr.from]);
        printf("  to =   %s\n", sqToStr[curr.to]);
        printf("  pT =   %s\n", pieceToStr[curr.pT]);
        printf("  pC =   %s\n", colorToStr[curr.pC]);
        printf("  capturedP = %s", pieceToStr[curr.capturedP]);
        printf("  isPromotion = %d\n", curr.isPromotion);
        printf("  isCapture = %d", curr.isCapture);
        printf("  isEnPassant = %d", curr.isEnPassant);
        printf("  isCastlingShort = %d", curr.isCastlingShort);
        printf("  isCastlingLong= %d\n", curr.isCastlingLong);
        printf("}\n");
    }
}

size_t MoveList::size()
{
    return this->moves.size();
}
