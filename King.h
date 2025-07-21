#ifndef KING_H
#define KING_H

#include "Position.h"
#include "Piece.h"

class King : public Piece { 
    public:
        King(char, Position, Board*);
        bool canMove(Move) override;
        std::vector<Move> getLegalMoves() override;
};

#endif
