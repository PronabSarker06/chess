#ifndef BOARD_H
#define BOARD_H

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
#include <iostream>

class Board { 

    std::vector<std::unique_ptr<Piece>> grid;
    std::vector<char> displayGrid; 
    bool whiteInCheck, blackInCheck;

    public:
        Board();
        bool isCheckmate();
        bool isStalemate();
        void makeMove(Move m);
        void display();
        bool passantable(Pawn& p);
        void castle(King &k, Rook &r);
};

#endif
