#include "Queen.h"
#include "Move.h"
#include "Board.h"

Queen::Queen(char c, Position p, Board* bptr) 
    : Piece(c, 'q', p, bptr) {}

bool Queen::canMove(Move) {

    return true;
    
}


std::vector<Move> Queen::getLegalMoves() {
    std::vector<Move> result;
    for (int row_change = -1; row_change < 2; ++row_change) {
        for (int col_change = -1; col_change < 2; ++col_change) {
            // A piece cannot move to itself
            if (row_change == 0 && col_change == 0) {
                continue;
            }
            Position to = {position.getCol() + col_change, position.getRow() + row_change};
            // Move in the direction until invalid move (ex. own pieces or boundary)
            while (to.valid()) {
                // Check if destination is empty
                if (bptr->getDisplayGrid()[to.to1D()] == '0') {
                    result.push_back(Move{position, to, this, nullptr});
                    to = {to.getCol() + col_change, to.getRow() + row_change};
                    continue;
                }
                // Check if destination is enemy piece
                if (bptr->getPieceAt(to) && this->colour != bptr->getPieceAt(to)->getColour()) {
                    result.push_back(Move{position, to, this, bptr->getPieceAt(to)});
                }
                break;
            }
        }
    }
    return result;
}
