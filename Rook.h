#ifndef ROOK_H
#define ROOK_H

#include "Position.h"
#include "Piece.h"

class Rook : public Piece { 
    public:
        Rook(char, Position, Board*);
        bool canMove(Move) override;
        std::vector<Move> getLegalMoves() override;
};

#endif
