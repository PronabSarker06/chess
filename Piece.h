#ifndef PIECE_H
#define PIECE_H

#include "Position.h"
#include <vector>

class Move; //Forward declaration
class Board;

class Piece {
    protected:
        char colour;
        char type;
        bool hasMoved;
        Position position;
        Board* bptr;

    public:
    
        //Pure virtual methods
        virtual std::vector<Move> getLegalMoves() = 0;

        Piece(char c, char t, Position p, Board* bptr);
        ~Piece() = default;
        bool operator==(const Piece& o);
        Position getPosition();
        char getType();
        char getColour();
        bool getHasMoved();
        bool kingSafe(Move m);

        void setMoved();
        void modPos(Position p);

};

#endif
