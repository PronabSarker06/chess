#include "King.h"
#include "Move.h"


King::King(char c, Position p, Board* bptr) 
    : Piece(c, 'k', p, bptr) {}

bool King::canMove(Move) {

    return true;

}

std::vector<Move> King::getLegalMoves() {

    std::vector<Move> result;

    return result;

}
