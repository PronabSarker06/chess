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
    Position white_king{4, 7};
    Position black_king{4, 0};

    public:
        Board();
        bool makeMove(Move m);
        void display();
        void initGraphics();
        std::stack<Move>& getHistory();
        Position getWhiteKing();
        void setWhiteKing(Position p);
        Position getBlackKing();
        void setBlackKing(Position p);
        void drawTile(Position pos, char piece = '0');
        void castle(King &k, Rook &r);
        bool isAttacked(Position square, char enemy_colour);
        std::vector<std::unique_ptr<Piece>>& getGrid () { return grid; }
        Piece* getPieceAt(const Position pos);
        std::vector<char>& getDisplayGrid();
        void setDisplayGrid(Position pos, char c);
        int Board::isCheckStalemate(char colour, bool& inCheck) {
};

#endif
