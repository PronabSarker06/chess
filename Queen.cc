#include "Queen.h"
#include "Move.h"

Queen::Queen(char c, Position p) 
    : Piece(c, 'q', p) {}

bool Queen::canMove(Move) {

    return true;
    
}

std::vector<Move> Queen::getLegalMoves() {

    std::vector<Move> result;

    return result;

}
