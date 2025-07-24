#ifndef KING_H
#define KING_H

#include "Position.h"
#include "Piece.h"

class King : public Piece { 
    public:
        King(char, Position, Board*);
        std::vector<Move> getLegalMoves() override;
};

#endif
