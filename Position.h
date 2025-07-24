#include <iostream>


#ifndef POSITION_H
#define POSITION_H

//A position on the board
class Position {

    int col;
    int row;

    public:

        Position(int _col, int _row);
        int getCol() const;
        int getRow() const;
        
        int to1D();
        bool valid();

        friend std::ostream& operator<< (std::ostream& out, const Position& pos);
        bool operator== (const Position& other);

};

#endif
