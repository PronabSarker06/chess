#include <iostream>


#ifndef POSITION_H
#define POSITION_H

//A position on the board
class Position {

    int col;
    int row;

    public:
        
        Position(int _col, int _row);
        int to1D();
        int getCol() const;
        int getRow() const;
        bool operator== (const Position& other);
        bool valid();

        friend std::ostream& operator<< (std::ostream& out, const Position& pos);

};

#endif
