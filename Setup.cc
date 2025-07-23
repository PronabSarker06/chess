#include "Setup.h"
#include <vector>

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
        for (int i = 0; i < b->getGrid().size(); ++i) { 
            Piece* p = b->getGrid()[i].get();
            if (p->getType() == 'k') {
                p->getColour() == 'w' ? b->setWhiteKing(p->getPosition()) : b->setBlackKing(p->getPosition());
            }
        }
        
        return true;
    }
    else { 
        std::cout << "Error: you have " << whiteKingCount << " white kings and " << blackKingCount << " black kings on the board." << std::endl;
        return false;
    }
}

void Setup::removePiece(Position p) { 
    auto it = b->getGrid().begin();
    for (; it != b->getGrid().end(); ++it) {
        if (it->get()->getPosition() == p) {
            break;
        }
    }
    b->getGrid().erase(it);
    b->drawTile(p);
}

void Setup::addPiece(Position p, char colour, char type) { 
    if (b->getPieceAt(p)) { 
        removePiece(p);
    }

    std::unique_ptr<Piece> newPiece;

    switch (type) {
        case 'p': newPiece = std::make_unique<Pawn>(colour, p, b); break;
        case 'n': newPiece = std::make_unique<Knight>(colour, p, b); break;
        case 'b': newPiece = std::make_unique<Bishop>(colour, p, b); break;
        case 'r': newPiece = std::make_unique<Rook>(colour, p, b);   break;
        case 'q': newPiece = std::make_unique<Queen>(colour, p, b);  break;
        case 'k': newPiece = std::make_unique<King>(colour, p, b);  break;
    }

    b->getGrid().emplace_back(std::move(newPiece));
    b->drawTile(p, (colour == 'w' ? std::toupper(type) : type));
}
