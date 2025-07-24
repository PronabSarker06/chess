#include "Knight.h"
#include "Move.h"
#include "Board.h"
#include <vector>

Knight::Knight(char c, Position p, Board* bptr) 
    : Piece(c, 'n', p, bptr) {}

bool Knight::canMove(Move) {

    return true;
    
}


std::vector<Move> Knight::getLegalMoves() {
    std::vector<Move> result;
    // Check all 8 possible moves
    std::vector<int> col_change = {2, 2, -2, -2, 1, 1, -1, -1};
    std::vector<int> row_change = {1, -1, 1, -1, 2, -2, 2, -2};
    for (int i = 0; i < 8; ++i) {
        Position to = {
            position.getCol() + col_change.at(i),
            position.getRow() + row_change.at(i)
        };
        if (to.valid()) {
            // Check if destination is empty
            if (bptr->getDisplayGrid()[to.to1D()] == '0') {
                if (kingSafe({position, to, this, nullptr})) result.push_back(Move{position, to, this, nullptr});
            }
            // Check if destination is an enemy piece
            else if (bptr->getPieceAt(to) && 
            this->colour != bptr->getPieceAt(to)->getColour()) {
                if (kingSafe({position, to, this, bptr->getPieceAt(to)})) result.push_back(Move{position, to, this, bptr->getPieceAt(to)});
            }
        }
    }
    return result;
}
