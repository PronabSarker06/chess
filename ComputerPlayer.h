#include "Game.h"

class ComputerPlayer { 
    int level;
    char colour;
    int moveCount;
    public:
        ComputerPlayer(int lvl, char colour);
        Move cMove (Board& b);
};
