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
#include <stack>
#include <algorithm>

class Board { 

    std::vector<std::unique_ptr<Piece>> grid;
    std::vector<char> displayGrid; 
    Xwindow graphicDisplay;
    std::stack<Move> history;
    Position whiteKingPosn{0,0};
    Position blackKingPosn{0,0};

    public:
        Board();
        bool isCheckmate(char colour);
        bool isStalemate();
        bool makeMove(Move m);
        void display();
        void initGraphics();
        std::stack<Move>& getHistory();
        void drawTile(Position pos, char piece = '0');
        void castle(King &k, Rook &r);
        bool isAttacked(Position square, char enemy_colour);
        std::vector<std::unique_ptr<Piece>>& getGrid () { return grid; }
        Piece* getPieceAt(const Position pos);
        std::vector<char>& getDisplayGrid();
        void setWhiteKingPosn(Position p);
        void setBlackKingPosn(Position p);
};

#endif
