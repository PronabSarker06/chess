#include "Piece.h"

Piece::Piece(char c, char t, Position p, Board* bptr)
    : colour{c}, type{t}, hasMoved{false}, position{p}, bptr {bptr} {}

Position Piece::getPosition() { 
    return this->position;
}

char Piece::getType() { 
    return this->type;
}

char Piece::getColour() { 
    return this->colour;
}
