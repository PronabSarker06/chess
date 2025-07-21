#ifndef PAWN_H
#define PAWN_H

#include "Position.h"
#include "Piece.h"
#include "Move.h"
#include <vector>

class Pawn : public Piece { 
    public:
        Pawn(char, Position);
        void promote();
        bool canMove(Move) override;
        std::vector<Move> getLegalMoves() override;
};

#endif
