#include "Piece.h"

Piece::Piece(char c, char t, Position p)
    : colour{c}, type{t}, hasMoved{false}, position{p} {}

Position Piece::getPosition() { 
    return this->position;
}

char Piece::getType() { 
    return this->type;
}

char Piece::getColour() { 
    return this->colour;
}