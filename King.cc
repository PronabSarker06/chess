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
  
   for (int col_change = -1; col_change <= 1; ++col_change) {
       for (int row_change = -1; row_change <= 1; ++row_change) {
           // cannot make a move to original position
           if (col_change == 0 && row_change == 0) continue;
           Position to = {
               this->position.getCol() + col_change,
               this->position.getRow() + row_change
           };
           if (!to.valid()) continue;
           // Check if square is empty or contains opponent's piece
           Piece* target = bptr->getPieceAt(to);
           // Destination can only be empty or an enemy piece
           if (target == nullptr || this->colour != target->getColour()) {
               result.emplace_back(this->position, to, this, target);
           }
       }
   }
   return result;
}
