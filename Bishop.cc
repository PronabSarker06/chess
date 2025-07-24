#include "Bishop.h"
#include "Move.h"
#include "Board.h"

Bishop::Bishop(char c, Position p, Board* bptr) 
    : Piece(c, 'b', p, bptr) {}

std::vector<Move> Bishop::getLegalMoves() {

    std::vector<Move> result;

    for (int vert = -1; vert <= 1; vert++){
        for (int hor = -1; hor <= 1; hor++){
            // Non-diagonal movements
            if (vert * hor == 0) continue;
            Position cur = {position.getCol() + hor, position.getRow() + vert};
            // Push in direction while blank and valid
            while (cur.valid() && bptr->getDisplayGrid()[cur.to1D()] == '0'){
                Move m {position, cur, this, nullptr, '0'};
                if (kingSafe(m)) result.push_back(m);
                cur = {cur.getCol() + hor, cur.getRow() + vert};
            }
            // If we can capture, ie not same color
            if (cur.valid() && bptr->getPieceAt(cur) && bptr->getPieceAt(cur)->getColour() != colour){
                Move m {position, cur, this, bptr->getPieceAt(cur), '0'};
                if (kingSafe(m)) result.push_back(m);
            }
        }
    }

    return result;

}
