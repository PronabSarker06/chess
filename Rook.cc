#include "Rook.h"
#include "Move.h"

Rook::Rook(char c, Position p, Board* bptr) 
    : Piece(c, 'r', p, bptr) {}

bool Rook::canMove(Move) {

    return true;
    
}

std::vector<Move> Rook::getLegalMoves() {

    std::vector<Move> result;

    return result;

}
