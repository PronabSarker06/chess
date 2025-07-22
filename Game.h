#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Piece.h"
#include "Move.h"

#include <vector>

class Game { 
    Board board;
    char curTurn;
    std::vector<Move> moveHistory;

    public:
        void startGame();
        void setup();
        void resign();
        void checkState();

        Game();
};

#endif