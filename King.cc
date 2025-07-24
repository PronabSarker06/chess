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
                if (kingSafe({this->position, to, this, bptr->getPieceAt(to)})) result.emplace_back(this->position, to, this, bptr->getPieceAt(to));
            }
        }
    }

    char enemyColour = colour == 'w' ? 'b' : 'w';

    // castles
    if (!hasMoved && !bptr->isAttacked(position, enemyColour)) {
        int row = position.getRow();

        // Castling to the left (queenside)
        Piece* leftrook = bptr->getPieceAt(Position{0, row});
        if (leftrook && leftrook->getType() == 'r' && !leftrook->getHasMoved()) {
            if (!bptr->getPieceAt(Position{1, row}) && 
                !bptr->getPieceAt(Position{2, row}) && 
                !bptr->getPieceAt(Position{3, row}) &&
                !bptr->isAttacked(Position{2, row}, enemyColour) &&
                !bptr->isAttacked(Position{3, row}, enemyColour)) {

                Position to = {2, row}; // king ends up on column 2
                if (kingSafe({position, to, this, nullptr})) result.emplace_back(position, to, this, nullptr); // add move
            }
        }

        // Castling to the right (kingside)
        Piece* rightrook = bptr->getPieceAt(Position{7, row});
        if (rightrook && rightrook->getType() == 'r' && !rightrook->getHasMoved()) {
            if (!bptr->getPieceAt(Position{5, row}) &&
                !bptr->getPieceAt(Position{6, row}) &&
                !bptr->isAttacked(Position{5, row}, enemyColour) &&
                !bptr->isAttacked(Position{6, row}, enemyColour)) { // all true? 

                Position to = {6, row}; // king ends up on column 6
                if (kingSafe({position, to, this, nullptr})) result.emplace_back(position, to, this, nullptr); // add move
            }
        }
    }

    return result;
    
}
