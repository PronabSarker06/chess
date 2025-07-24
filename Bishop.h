#ifndef BISHOP_H
#define BISHOP_H

#include "Position.h"
#include "Piece.h"

class Bishop : public Piece { 
    public:
        Bishop(char, Position, Board*);
        std::vector<Move> getLegalMoves() override;
};

#endif
