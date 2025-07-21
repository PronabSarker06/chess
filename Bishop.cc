#include "Bishop.h"
#include "Move.h"

Bishop::Bishop(char c, Position p) 
    : Piece(c, 'b', p) {}

bool Bishop::canMove(Move) {

    return true;
    
}

std::vector<Move> Bishop::getLegalMoves() {

    std::vector<Move> result;

    return result;

}
