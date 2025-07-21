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

    int colourFactor = this->colour == 'b' ? -1 : 1;
    Position f1pos = {this->position.getCol(), this->position.getRow() + 1 * colourFactor};
    Move forward1 = {this->position, f1pos, this, nullptr, '0'};
    result.emplace_back(forward1);

    //only if first move, can go up 2
    if (!hasMoved){
        Position f2pos = {this->position.getCol(), this->position.getRow() + 2 * colourFactor};
        Move forward2 = {this->position, f2pos, this, nullptr, '0'};
        result.emplace_back(forward2);
    }
    
    return result;

}
