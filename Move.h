#ifndef MOVE_H
#define MOVE_H

#include "Piece.h"
#include "Position.h"

//A position on the board
class Move {

    Position from;
    Position to;
    Piece* pieceMoved;
    Piece* pieceCaptured;
    char promotionType;

    public:
        Move(Position from, Position to, Piece* pieceMoved, Piece* pieceCaptured = nullptr, char promoType = '0');
        Piece* getPieceMoved();
        Position getTo();
        Position getFrom();
        bool operator==(Move& o) const;

};

#endif
