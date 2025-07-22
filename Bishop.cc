#include "Bishop.h"
#include "Move.h"
#include "Board.h"

Bishop::Bishop(char c, Position p, Board* bptr) 
    : Piece(c, 'b', p, bptr) {}

bool Bishop::canMove(Move) {

    return true;
    
}

std::vector<Move> Bishop::getLegalMoves() {

    std::vector<Move> result;

    for (int vert = -1; vert <= 1; vert++){
        for (int hor = -1; hor <= 1; hor++){
            if (vert * hor == 0) continue; //non diagonal movements
            Position cur = {position.getCol() + hor, position.getRow() + vert};
            //push in direction while blank and valid
            while (cur.valid() && bptr->getDisplayGrid()[cur.to1D()] == '0'){
                result.push_back(Move{position, cur, this, nullptr, '0'});
                cur = {cur.getCol() + hor, cur.getRow() + vert};
            }
            //If we can capture, ie not same color
            if (cur.valid() && bptr->getPieceAt(cur)->getColour() != colour){
                result.push_back(Move{position, cur, this, bptr->getPieceAt(cur), '0'});
            }
        }
    }

    return result;

}
