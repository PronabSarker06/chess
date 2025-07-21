#include "Knight.h"
#include "Move.h"

Knight::Knight(char c, Position p, Board* bptr) 
    : Piece(c, 'n', p, bptr) {}

bool Knight::canMove(Move) {

    return true;
    
}

std::vector<Move> Knight::getLegalMoves() {

    std::vector<Move> result;

    return result;

}
