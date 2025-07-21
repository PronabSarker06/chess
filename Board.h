#include "Piece.h"
#include "Move.h"

#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

#include <vector>
#include <memory>

class Board { 

    std::vector<std::unique_ptr<Piece>> grid;
    bool whiteInCheck, blackInCheck;

    public:
        bool isCheckmate();
        bool isStalemate();
        void makeMove(Move m);
        void display();
        bool passantable(Pawn& p);
        void castle(King &k, Rook &r);
};