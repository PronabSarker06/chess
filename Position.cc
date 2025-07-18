#include "Position.h"

Position::Position (int _col, int _row) : col {_col}, row {_row} {}

//Returns 1D indexing
int Position::to1D () {
    return row * 8 + col; //a row is 8 cols, space accordingly in 1D
}
