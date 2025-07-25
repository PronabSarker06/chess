#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include "Setup.h"

#include <vector>

class Game { 

    Board board;
    char whoseTurn;
    std::vector<Move> moveHistory;
    bool gameActive = false;

    public:
        void startGame();
        void setup();
        void resign();
        void checkState();
        void makeMove(char, char, char, char, char);
        void display();
        bool gameOn();
        void flipTurn();

        Game();

        Board& getBoard();
        char getTurn();
};

#endif
