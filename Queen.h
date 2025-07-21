#include "Position.h"
#include "Piece.h"

class Queen : public Piece { 
    public:
        Queen(char, Position);
        bool canMove(Move) override;
        std::vector<Move> getLegalMoves() override;
};