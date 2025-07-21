#include "Pawn.h"
#include "Move.h"

Pawn::Pawn(char c, Position p, Board* bptr) 
    : Piece(c, 'p', p, bptr) {}

void promote() {

}

bool Pawn::canMove(Move) {

    return true;
    
}

std::vector<Move> Pawn::getLegalMoves() {

    std::vector<Move> result;

    Position f1pos = {this->position.getCol(), this->position.getRow() + 1};
    Move forward1 = {this->position, f1pos, this, nullptr, '0'};
    result.emplace_back(forward1);

    return result;

}
