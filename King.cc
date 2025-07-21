#include "King.h"
#include "Move.h"


King::King(char c, Position p, Board* bptr) 
    : Piece(c, 'k', p, bptr) {}

bool King::canMove(Move) {

    return true;

}

std::vector<Move> King::getLegalMoves() {

    std::vector<Move> result;

    // set colour of the King
    this->colour == 'b' ? -1 : 1;

    // check each available move. Kings can move at most 1 vertically + 1 horizontally
    for (int col_change = -1; col_change <= 1; ++col_change) {
        for (int row_change = -1; row_change <= 1; ++row_change) {
            Position to = {this->position.getCol() + col_change, this->position.getRow() + row_change};
            // Destination must be valid, cannot capture its own, and not step into check
            if (to.valid() && this->colour !=  bptr->grid[to.to1D()]->colour) {
                Move move = {this->position, to, this, bptr->grid[to.to1D()]};
                result.emplace_back(move);
            }
        }
    }
    return result;

}
