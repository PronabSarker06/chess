#include "Piece.h"

Piece::Piece(char c, char t, Position p)
    : colour{c}, type{t}, hasMoved{false}, position{p} {}