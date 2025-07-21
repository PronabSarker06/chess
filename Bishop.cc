#include "Bishop.h"
#include "Move.h"

Bishop::Bishop(char c, Position p, Board* bptr) 
    : Piece(c, 'b', p, bptr) {}

bool Bishop::canMove(Move) {

    return true;
    
}

std::vector<Move> Bishop::getLegalMoves() {

    std::vector<Move> result;

    return result;

}
