#include "Queen.h"
#include "Move.h"

Queen::Queen(char c, Position p, Board* bptr) 
    : Piece(c, 'q', p, bptr) {}

bool Queen::canMove(Move) {

    return true;
    
}

std::vector<Move> Queen::getLegalMoves() {

    std::vector<Move> result;

    return result;

}
