#include "ComputerPlayer.h" 
#include <random>

ComputerPlayer::ComputerPlayer(int l, char c) : level{l}, colour{c}, moveCount{0} {};

Move lv1Move(Board& b, char colour) { // finds first piece of same colour in grid, returns first legal move

    std::random_device rd;
    std::mt19937 gen(rd());

    int gridIndex;
    auto& grid = b.getGrid();

    // Keep picking until we find a piece with at least one legal move
    while (true) {
        std::uniform_int_distribution<> gridDist(0, grid.size() - 1);
        gridIndex = gridDist(gen);

        auto piecePtr = grid[gridIndex].get();
        if (piecePtr && !piecePtr->getLegalMoves().empty()) {
            break;
        }
    }

    // Now pick a random legal move from that piece
    const auto& legalMoves = grid[gridIndex]->getLegalMoves();
    std::uniform_int_distribution<> moveDist(0, legalMoves.size() - 1);
    int moveIndex = moveDist(gen);

    return grid[gridIndex].get()->getLegalMoves()[moveIndex];

}

Move lv2Move(Board& b, char colour) { 
    for (size_t i = 0; i < b.getGrid().size(); ++i) { 
        if (b.getGrid()[i].get()->getColour() == colour) { 
            Piece* p = b.getGrid()[i].get();
            for (auto &move : p->getLegalMoves()) { 
                if (move.getCap()) return move; // returns a capturing move if possible
                
            }
        }
    }

    return lv1Move(b, colour); // else returns lv1Move

}

Move lv3Move(Board& b, char colour) { 
    for (size_t i = 0; i < b.getGrid().size(); ++i) { 
        if (b.getGrid()[i].get()->getColour() == colour) { 
            Piece* p = b.getGrid()[i].get();
            for (auto &move : p->getLegalMoves()) { 
                if (!b.isAttacked(move.getTo(), (colour == 'w'? 'b' : 'w'))) return move;
            }
        }
    }

    return lv2Move(b, colour);
}

Move lv4Move(Board& b, char colour, int& mc) { 
    if (mc < 5) { 
        std::vector<Move> whiteOpening{ 
            {{3, 6}, {3, 4}, b.getPieceAt({3, 6}), nullptr}, // queen's gambit
            {{2, 6}, {2, 4}, b.getPieceAt({2, 6}), nullptr},
            {{1, 7}, {2, 5}, b.getPieceAt({1, 7}), nullptr},
            {{5, 7}, {6, 6}, b.getPieceAt({5, 7}), nullptr},
            {{4, 7}, {3, 6}, b.getPieceAt({4, 7}), nullptr}
        };

        std::vector<Move> blackOpening{ 
            {{3, 1}, {3, 3}, b.getPieceAt({3, 1}), nullptr}, // slav defense
            {{2, 1}, {2, 3}, b.getPieceAt({2, 1}), nullptr},
            {{1, 0}, {2, 2}, b.getPieceAt({1, 0}), nullptr},
            {{5, 0}, {6, 2}, b.getPieceAt({5, 0}), nullptr},
            {{4, 0}, {6, 0}, b.getPieceAt({4, 0}), nullptr} 
        };

        mc++;

        if (colour == 'w') { 
            if (b.getPieceAt(whiteOpening[mc-1].getFrom())) return whiteOpening[mc-1];
            else return lv3Move(b, colour);
        } else { 
            if (b.getPieceAt(blackOpening[mc-1].getFrom())) return blackOpening[mc-1];
            else return lv3Move(b, colour);
        }
    }
    else return lv3Move(b, colour);
}

Move ComputerPlayer::cMove(Board& b) { 
    switch (level) { 
        case 1: return lv1Move(b, colour);
        case 2: return lv2Move(b, colour);
        case 3: return lv3Move(b, colour);
        case 4: return lv4Move(b, colour, moveCount);
    }
}

