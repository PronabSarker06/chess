#include "Pawn.h"
#include "Move.h"
#include "Board.h"

Pawn::Pawn(char c, Position p, Board* bptr) 
    : Piece(c, 'p', p, bptr) {}

void promote() {

}

bool Pawn::canMove(Move) {

    return true;
    
}

std::vector<Move> Pawn::getLegalMoves() {

    std::vector<Move> result;
    int colourFactor = colour == 'b' ? 1 : -1; //flip direction depending on color

    //moving forward by 1
    //if nothing blocking the pawn
    Position f1pos = {position.getCol(), position.getRow() + 1 * colourFactor};
    if (f1pos.valid() && bptr->getDisplayGrid()[f1pos.to1D()] == '0'){
        Move forward1 = {position, f1pos, this, nullptr, '0'};
        result.emplace_back(forward1);
    }
    
    //try moving up 2
    //only if first move, can go up 2, check nothing blocks
    Position f2pos = {position.getCol(), position.getRow() + 2 * colourFactor};
    if (!hasMoved && f2pos.valid() && bptr->getDisplayGrid()[f2pos.to1D()] == '0'){
        Move forward2 = {position, f2pos, this, nullptr, '0'};
        result.emplace_back(forward2);
    }

    // cap left
    Position clpos = {position.getCol() - 1, position.getRow() + 1 * colourFactor};
    Piece* p = bptr->getPieceAt(clpos);
    if (p && p->getColour() != colour) {
        Move capleft = {position, clpos, this, p, '0'};
        result.emplace_back(capleft);
    }

    //cap right
    Position crpos = {position.getCol() + 1, position.getRow() + 1 * colourFactor}; // good cap checks
    Piece* p = bptr->getPieceAt(crpos);
    if (p && p->getColour() != colour) {
        Move capright = {position, crpos, this, p, '0'};
        result.emplace_back(capright);
    }
    
    return result;

}
