#include "Game.h"

class ComputerPlayer { 
    int level;
    char colour;
    public:
        ComputerPlayer(int lvl, char colour);
        Move lv1Move(Board* b);
        Move lv2Move(Board* b);
        Move lv3Move(Board* b);
        Move lv4Move(Board* b);
};