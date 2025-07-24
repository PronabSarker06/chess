#include "Rook.h"
#include "Move.h"
#include "Board.h"

Rook::Rook(char c, Position p, Board* bptr) 
    : Piece(c, 'r', p, bptr) {}

bool Rook::canMove(Move) {

    return true;
    
}

std::vector<Move> Rook::getLegalMoves() {

    std::vector<Move> result;

    for (int vert = -1; vert <= 1; vert++){
        for (int hor = -1; hor <= 1; hor++){
            if (abs(vert) + abs(hor) != 1) { continue; } //skip directions that are not in one direction
            Position cur = {position.getCol() + hor, position.getRow() + vert};
            while (cur.valid() && bptr->getDisplayGrid()[cur.to1D()] == '0'){
                if (kingSafe({position, cur, this, nullptr, '0'})) result.push_back(Move{position, cur, this, nullptr, '0'}); //valid move
                cur = {cur.getCol() + hor, cur.getRow() + vert};
            }
            //Attacking a piece upwards
            if (cur.valid() && bptr->getPieceAt(cur)->getColour() != colour){
                if (kingSafe({position, cur, this, bptr->getPieceAt(cur), '0'})) result.push_back(Move{position, cur, this, bptr->getPieceAt(cur), '0'});
            }
        }
    }    

    return result;

}
