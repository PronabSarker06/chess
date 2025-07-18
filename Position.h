#ifndef POSITION_H
#define POSITION_H

//A position on the board
class Position {

    int col;
    int row;

    public:
        
        Position(int _col, int _row);
        int to1D();

};

#endif
