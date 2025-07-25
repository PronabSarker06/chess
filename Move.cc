#include "Move.h"
#include "Position.h"
#include "Piece.h"

//MIL to handle reference
Move::Move(Position from, Position to, Piece* pieceMoved, Piece* pieceCaptured, char promoType)
    : from {from}, to {to}, pieceMoved {pieceMoved}, pieceCaptured {pieceCaptured}, promotionType {promoType} {}

Piece* Move::getPieceMoved() { 
    return pieceMoved;
}

Position Move::getTo() { 
    return to;
}

Position Move::getFrom() { 
    return from;
}

bool Move::operator==(Move& o) const { 
    return (from == o.from && to == o.to && pieceCaptured == o.pieceCaptured && pieceMoved == o.pieceMoved && promotionType == o.promotionType);
}

Piece* Move::getCap() { 
    return pieceCaptured;
}

char Move::getPromoType() { 
    return promotionType;
}

std::ostream& operator<< (std::ostream& out, const Move& m) {
    out << "Move: " << m.from << ", " << m.to << (m.promotionType == '0' ? "" : ", Promotion to: " + m.promotionType);
    return out;
}
