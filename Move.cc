#include "Move.h"
#include "Position.h"
#include "Piece.h"

//MIL to handle reference
Move::Move(Position from, Position to, Piece* pieceMoved, Piece* pieceCaptured, char promoType)
    : from {from}, to {to}, pieceMoved {pieceMoved}, pieceCaptured {pieceCaptured}, promotionType {promoType} {}

Piece* Move::getPieceMoved() { 
    return this->pieceMoved;
}

Position Move::getTo() { 
    return this->to;
}

Position Move::getFrom() { 
    return this->from;
}

bool Move::operator==(Move& o) const { 
    return (from == o.from && to == o.to && pieceCaptured == o.pieceCaptured && pieceMoved == o.pieceMoved && promotionType == o.promotionType);
}