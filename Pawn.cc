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
    Position f1pos = {position.getCol(), position.getRow() + 1 * colourFactor}; // add promo
    if (f1pos.valid() && bptr->getDisplayGrid()[f1pos.to1D()] == '0'){
        if (position.getRow() == (colour == 'b' ? 6 : 1)) {
            Move knightPromo = {position, f1pos, this, nullptr, 'n'}; // promo moves
            Move bishopPromo = {position, f1pos, this, nullptr, 'b'}; 
            Move rookPromo = {position, f1pos, this, nullptr, 'r'}; 
            Move queenPromo = {position, f1pos, this, nullptr, 'q'}; 

            result.emplace_back(knightPromo);
            result.emplace_back(bishopPromo);
            result.emplace_back(rookPromo);
            result.emplace_back(queenPromo);
        } else { 
            Move forward1 = {position, f1pos, this, nullptr, '0'};
            result.emplace_back(forward1);
        }
    }
    
    //try moving up 2
    //only if first move, can go up 2, check nothing blocks
    Position f2pos = {position.getCol(), position.getRow() + 2 * colourFactor}; // add promo (setup can have a pawn promote on first move)
    if (!hasMoved && f2pos.valid() && bptr->getDisplayGrid()[f2pos.to1D()] == '0'){
        if (position.getRow() == (colour == 'b' ? 5 : 2)) {
            Move knightPromo = {position, f2pos, this, nullptr, 'n'}; // promo moves
            Move bishopPromo = {position, f2pos, this, nullptr, 'b'}; 
            Move rookPromo = {position, f2pos, this, nullptr, 'r'}; 
            Move queenPromo = {position, f2pos, this, nullptr, 'q'}; 

            result.emplace_back(knightPromo);
            result.emplace_back(bishopPromo);
            result.emplace_back(rookPromo);
            result.emplace_back(queenPromo);
        } else { 
            Move forward2 = {position, f2pos, this, nullptr, '0'};
            result.emplace_back(forward2);
        }
    }

    // cap left
    Position clpos = {position.getCol() - 1, position.getRow() + 1 * colourFactor}; // add promo
    Piece* p = bptr->getPieceAt(clpos);
    if (p && p->getColour() != colour) {
        if (position.getRow() == (colour == 'b' ? 6 : 1)) {
            Move knightPromo = {position, clpos, this, p, 'n'}; // promo moves
            Move bishopPromo = {position, clpos, this, p, 'b'}; 
            Move rookPromo = {position, clpos, this, p, 'r'}; 
            Move queenPromo = {position, clpos, this, p, 'q'}; 

            result.emplace_back(knightPromo);
            result.emplace_back(bishopPromo);
            result.emplace_back(rookPromo);
            result.emplace_back(queenPromo);
        } else { 
            Move capleft = {position, clpos, this, p, '0'};
            result.emplace_back(capleft);
        }
    }

    //cap right
    Position crpos = {position.getCol() + 1, position.getRow() + 1 * colourFactor}; // add promo
    p = bptr->getPieceAt(crpos);
    if (p && p->getColour() != colour) {
        if (position.getRow() == (colour == 'b' ? 6 : 1)) {
            Move knightPromo = {position, crpos, this, p, 'n'}; // promo moves
            Move bishopPromo = {position, crpos, this, p, 'b'}; 
            Move rookPromo = {position, crpos, this, p, 'r'}; 
            Move queenPromo = {position, crpos, this, p, 'q'}; 

            result.emplace_back(knightPromo);
            result.emplace_back(bishopPromo);
            result.emplace_back(rookPromo);
            result.emplace_back(queenPromo);
        } else { 
            Move capright = {position, crpos, this, p, '0'};
            result.emplace_back(capright);
        }
    }
    
    return result;

}
