#include "Position.h"
#include "Piece.h"

class Bishop : public Piece { 
    public:
        Bishop(char, Position);
        bool canMove(Move) override;
        std::vector<Move> getLegalMoves() override;
};