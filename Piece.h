#ifndef PIECE_H
#define PIECE_H

#include "Position.h"
#include <vector>

class Move; //Forward declaration

class Piece {

    char colour;
    char type;
    bool hasMoved;
    Position position;

    public:
    
        //Pure virtual methods
        virtual bool canMove(Move) = 0;
        virtual std::vector<Move> getLegalMoves() = 0;

};

#endif
