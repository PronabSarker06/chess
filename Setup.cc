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

    //Check for pawn on first or last row
    for (int i = 0; i < 8; i++){
        if (b->getPieceAt({i, 0}) && b->getPieceAt({i, 0})->getType() == 'p' || b->getPieceAt({i, 7}) && b->getPieceAt({i, 7})->getType() == 'p'){
            std::cout << "Error: Pawn on first or last row" << std::endl;
            return false;
        }
    }

    if (whiteKingCount == 1 && blackKingCount == 1) { 
        for (int i = 0; i < b->getGrid().size(); ++i) { 
            Piece* p = b->getGrid()[i].get();
            std::cout << "piece " << p->getType() << '\n';
            if (p->getType() == 'k') {
                std::cout << p->getPosition() << " colour: " << p->getColour() << " isattacked: " << b->isAttacked(p->getPosition(), p->getColour() == 'w' ? 'b' : 'w') << '\n';
                if (b->isAttacked(p->getPosition(), p->getColour() == 'w' ? 'b' : 'w')) {
                    std::cout << "Error: " << (p->getColour() == 'w' ? "White" : "Black") << " king is in check" << std::endl;
                    return false;
                }
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
    if (it != b->getGrid().end()) b->getGrid().erase(it);
    b->drawTile(p);
    b->setDisplayGrid(p, '0');
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
    b->setDisplayGrid(p, (colour == 'w' ? std::toupper(type) : type));
}
