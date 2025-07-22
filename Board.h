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
#include "window.h"

#include <vector>
#include <memory>
#include <iostream>

class Board { 

    std::vector<std::unique_ptr<Piece>> grid;
    std::vector<char> displayGrid; 
    bool whiteInCheck, blackInCheck;
    Xwindow graphicDisplay;

    public:
        Board();
        bool isCheckmate(char colour);
        bool isStalemate();
        bool makeMove(Move m);
        void display();
        void initGraphics();
        bool passantable(Pawn& p);
        void castle(King &k, Rook &r);
        bool isAttacked(Position square, char enemy_colour);
        std::vector<std::unique_ptr<Piece>>& getGrid () { return grid; }
        Piece* getPieceAt(const Position pos);
        std::vector<char>& getDisplayGrid();
};

#endif
