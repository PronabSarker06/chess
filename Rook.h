#include "Position.h"
#include "Piece.h"

class Rook : public Piece { 
    public:
        Rook(char, Position);
        bool canMove(Move) override;
        std::vector<Move> getLegalMoves() override;
};