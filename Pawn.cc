#include "Pawn.h"
#include "Move.h"

Pawn::Pawn(char c, Position p) 
    : Piece(c, 'p', p) {}

void promote() {
    
}

bool Pawn::canMove(Move) {

    return true;
    
}

std::vector<Move> Pawn::getLegalMoves() {

    std::vector<Move> result;

    return result;

}
