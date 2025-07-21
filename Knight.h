#ifndef KNIGHT_H
#define KNIGHT_H

#include "Position.h"
#include "Piece.h"

class Knight : public Piece { 
    public:
        Knight(char, Position, Board*);
        bool canMove(Move) override;
        std::vector<Move> getLegalMoves() override;
};

#endif
