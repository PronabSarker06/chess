#include "King.h"
#include "Move.h"


King::King(char c, Position p) 
    : Piece(c, 'k', p) {}

bool King::canMove(Move) {

    return true;
    
}

std::vector<Move> King::getLegalMoves() {

    std::vector<Move> result;

    return result;

}
