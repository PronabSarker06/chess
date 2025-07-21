#include "Position.h"
#include "Piece.h"

class Knight : public Piece { 
    public:
        Knight(char, Position);
        bool canMove(Move) override;
        std::vector<Move> getLegalMoves() override;
};