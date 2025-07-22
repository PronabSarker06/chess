#include "Position.h"

Position::Position (int _col, int _row) : col {_col}, row {_row} {}

//Returns 1D indexing
int Position::to1D () {
    return row * 8 + col; //a row is 8 cols, space accordingly in 1D
}

int Position::getCol() const { 
    return this->col;
}

int Position::getRow() const { 
    return this->row;
}

bool Position::operator== (const Position& other) {
    return row == other.row && col == other.col;
}

bool Position::valid() {
    return col >= 0 && col < 8 && row >= 0 && row < 8;
}

std::ostream& operator<< (std::ostream& out, const Position& pos){
    out << pos.getCol() << ' ' << pos.getRow();
    return out;
}
