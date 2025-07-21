#ifndef QUEEN_H
#define QUEEN_H

#include "Position.h"
#include "Piece.h"

class Queen : public Piece { 
    public:
        Queen(char, Position, Board*);
        bool canMove(Move) override;
        std::vector<Move> getLegalMoves() override;
};

#endif
