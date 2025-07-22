#include "King.h"
#include "Move.h"
#include "Board.h"

King::King(char c, Position p, Board* bptr) 
    : Piece(c, 'k', p, bptr) {}

bool King::canMove(Move) {

    return true;

}


std::vector<Move> King::getLegalMoves() {

    std::vector<Move> result;
    // Regular moves for King
    for (int col_change = -1; col_change <= 1; ++col_change) {
        for (int row_change = -1; row_change <= 1; ++row_change) {
            // A piece cannot move to itself
            if (row_change == 0 && col_change == 0) {
                continue;
            }
            Position to = {
                this->position.getCol() + col_change,
                this->position.getRow() + row_change
            };
            if (!to.valid()) {
                continue;
            }
            // Destination can only be empty or an enemy piece
            if (bptr->getPieceAt(to) == nullptr
            || this->colour != bptr->getPieceAt(to)->getColour()) {
                result.emplace_back(this->position, to, this, bptr->getPieceAt(to));
            }
        }
    }
    return result;
    
}
