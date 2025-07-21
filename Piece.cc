#include "Piece.h"

Piece::Piece(char c, char t, Position p, Board* bptr)
    : colour{c}, type{t}, hasMoved{false}, position{p}, bptr {bptr} {}

bool Piece::operator==(const Piece& o) { 
    return (colour == o.colour && type == o.type && hasMoved == o.hasMoved && position == o.position && bptr == o.bptr);
}

Position Piece::getPosition() { 
    return this->position;
}

void Piece::setMoved() { 
    hasMoved = true;
}

char Piece::getType() { 
    return this->type;
}

char Piece::getColour() { 
    return this->colour;
}

void Piece::modPos(Position p) { 
    this->position = p;
}