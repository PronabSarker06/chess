#ifndef SETUP_H
#define SETUP_H

#include "Board.h"

class Setup { 
    Board b;

    public: 
        Setup(Board b);
        bool valid();
        void addPiece(Position p, char colour, char type);
        void removePiece(Position p);
};

#endif