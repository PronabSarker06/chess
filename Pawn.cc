#include "Pawn.h"
#include "Move.h"
#include "Board.h"

Pawn::Pawn(char c, Position p, Board* bptr) 
    : Piece(c, 'p', p, bptr) {}

std::vector<Move> Pawn::getLegalMoves() {

    std::vector<Move> result;

    // Flip direction depending on color
    int colourFactor = colour == 'b' ? 1 : -1;

    // Moving forward by 1 if nothing blocking the pawn. Also consider promotions
    Position f1pos = {position.getCol(), position.getRow() + 1 * colourFactor};
    if (f1pos.valid() && bptr->getDisplayGrid()[f1pos.to1D()] == '0'){
        if (position.getRow() == (colour == 'b' ? 6 : 1)) {
            Move knightPromo = {position, f1pos, this, nullptr, 'N'};
            Move bishopPromo = {position, f1pos, this, nullptr, 'B'}; 
            Move rookPromo = {position, f1pos, this, nullptr, 'R'}; 
            Move queenPromo = {position, f1pos, this, nullptr, 'Q'}; 

            if (kingSafe(knightPromo)) result.emplace_back(knightPromo);
            if (kingSafe(bishopPromo)) result.emplace_back(bishopPromo);
            if (kingSafe(rookPromo)) result.emplace_back(rookPromo);
            if (kingSafe(queenPromo)) result.emplace_back(queenPromo);
        } else { 
            Move forward1 = {position, f1pos, this, nullptr, '0'};
            if (kingSafe(forward1)) result.emplace_back(forward1);
        }
    }
    
    // Move up 2 if first move and nothing blocks. Also consider promos
    Position f2pos = {position.getCol(), position.getRow() + 2 * colourFactor};
    if (!hasMoved && f2pos.valid() && bptr->getDisplayGrid()[f2pos.to1D()] == '0' && bptr->getDisplayGrid()[f1pos.to1D()] == '0'){
        if (position.getRow() == (colour == 'b' ? 5 : 2)) {
            Move knightPromo = {position, f2pos, this, nullptr, 'N'};
            Move bishopPromo = {position, f2pos, this, nullptr, 'B'}; 
            Move rookPromo = {position, f2pos, this, nullptr, 'R'}; 
            Move queenPromo = {position, f2pos, this, nullptr, 'Q'}; 

            if (kingSafe(knightPromo)) result.emplace_back(knightPromo);
            if (kingSafe(bishopPromo)) result.emplace_back(bishopPromo);
            if (kingSafe(rookPromo)) result.emplace_back(rookPromo);
            if (kingSafe(queenPromo)) result.emplace_back(queenPromo);
        } else { 
            Move forward2 = {position, f2pos, this, nullptr, '0'};
            if (kingSafe(forward2)) result.emplace_back(forward2);
        }
    }

    // Capture left. Also consider promo
    Position clpos = {position.getCol() - 1, position.getRow() + 1 * colourFactor};
    Piece* p = bptr->getPieceAt(clpos);
    if (p && p->getColour() != colour) {
        if (position.getRow() == (colour == 'b' ? 6 : 1)) {
            Move knightPromo = {position, clpos, this, p, 'N'};
            Move bishopPromo = {position, clpos, this, p, 'B'}; 
            Move rookPromo = {position, clpos, this, p, 'R'}; 
            Move queenPromo = {position, clpos, this, p, 'Q'}; 

            if (kingSafe(queenPromo)) result.emplace_back(queenPromo);
            if (kingSafe(knightPromo)) result.emplace_back(knightPromo);
            if (kingSafe(bishopPromo)) result.emplace_back(bishopPromo);
            if (kingSafe(rookPromo)) result.emplace_back(rookPromo);
        } else { 
            Move capleft = {position, clpos, this, p, '0'};
            if (kingSafe(capleft)) result.emplace_back(capleft);
        }
    }

    // Capture right. Also consider promo
    Position crpos = {position.getCol() + 1, position.getRow() + 1 * colourFactor};
    p = bptr->getPieceAt(crpos);
    if (p && p->getColour() != colour) {
        if (position.getRow() == (colour == 'b' ? 6 : 1)) {
            Move knightPromo = {position, crpos, this, p, 'N'};
            Move bishopPromo = {position, crpos, this, p, 'B'}; 
            Move rookPromo = {position, crpos, this, p, 'R'}; 
            Move queenPromo = {position, crpos, this, p, 'Q'}; 

            if (kingSafe(queenPromo)) result.emplace_back(queenPromo);
            if (kingSafe(knightPromo)) result.emplace_back(knightPromo);
            if (kingSafe(bishopPromo)) result.emplace_back(bishopPromo);
            if (kingSafe(rookPromo)) result.emplace_back(rookPromo);
        } else { 
            Move capright = {position, crpos, this, p, '0'};
            if (kingSafe(capright)) result.emplace_back(capright);
        }
    }

    // Check En Passant
    if (!bptr->getHistory().empty()) {
        // Since En Passant is temporary, check last move
        Move last = bptr->getHistory().top();
        // En Passant can only follow a double move, so check distance = 2
        if (last.getPieceMoved()->getType() == 'p'
        && last.getPieceMoved()->getColour() != colour
        && abs(last.getFrom().getRow() - last.getTo().getRow()) == 2) {
            // Check if adjacent to pawn
            if (position.getRow() == last.getTo().getRow()
            && abs(position.getCol() - last.getTo().getCol()) == 1) {
                Position captureP(last.getTo().getCol(), 
                                position.getRow() + colourFactor);
                Move ep(position, captureP, this, nullptr);
                if (kingSafe(ep)) result.emplace_back(ep);
            }
        }
    }

    return result;

}
