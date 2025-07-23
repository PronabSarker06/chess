#include "Setup.h"

Setup::Setup(Board* b) : b{b} {}

bool Setup::valid() { 
    int whiteKingCount = 0;
    int blackKingCount = 0;
    for (int i = 0; i < b->getGrid().size(); ++i) { 
        Piece* p = b->getGrid()[i].get();
        if (p->getType() == 'k') {
            p->getColour() == 'w' ? whiteKingCount++ : blackKingCount++;
        }
    }

    if (whiteKingCount == 1 && blackKingCount == 1) { 
        return true;
    }
    else { 
        std::cout << "Error: you have " << whiteKingCount << " white kings and " << blackKingCount << " black kings on the board." << std::endl;
        return false;
    }
}

void Setup::removePiece(Position p) { 
    for (auto it = b->getGrid().begin(); it != b->getGrid().end(); ++it) {
        if (it->get()->getPosition() == p) {
            b->getGrid().erase(it);
            break;
        }
    }

    b->drawTile(p);
}

void Setup::addPiece(Position p, char colour, char type) { 
    if (b->getPieceAt(p)) { 
        removePiece(p);
    }

    std::unique_ptr<Piece> newPiece;

    switch (type) {
        case 'N': newPiece = std::make_unique<Knight>(colour, p, b); break;
        case 'B': newPiece = std::make_unique<Bishop>(colour, p, b); break;
        case 'R': newPiece = std::make_unique<Rook>(colour, p, b);   break;
        case 'Q': newPiece = std::make_unique<Queen>(colour, p, b);  break;
    }

    b->getGrid().emplace_back(newPiece);
    b->drawTile(p, (colour == 'w' ? std::toupper(type) : type));
}