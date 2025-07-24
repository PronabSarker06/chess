#ifndef KNIGHT_H
#define KNIGHT_H

#include "Position.h"
#include "Piece.h"

class Knight : public Piece { 
    public:
        Knight(char, Position, Board*);
        std::vector<Move> getLegalMoves() override;
};

#endif
