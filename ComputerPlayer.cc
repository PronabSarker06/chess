#include "ComputerPlayer.h" 
#include <random>

ComputerPlayer::ComputerPlayer(int l, char c) : level{l}, colour{c} {};

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
        if (piecePtr && piecePtr->getColour() == colour && !piecePtr->getLegalMoves().empty()) {
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

int pieceValue(char p) {
    if (p == 'p' || p == 'P') {
        return 1;
    } else if (p == 'b' || p == 'n' || p == 'B' || p == 'N') {
        return 3;
    } else if (p == 'r' || p == 'R') {
        return 5;
    } else if (p == 'q' || p == 'Q') {
        return 9;
    } else {
        return 0;
    }
}

Move lv4Move(Board& b, char colour) {
    Move random = lv1Move(b, colour); // default fallback
    Move bestMove = random;
    int max_score = INT_MIN;
    for (size_t i = 0; i < b.getGrid().size(); ++i) {
        Piece* p = b.getGrid()[i].get();
        if (!p || p->getColour() != colour) {
            continue;
        }
        for (auto &move : p->getLegalMoves()) {
            // only check captures
            if (!move.getCap()) {
                continue; 
            }
            // Evaluate position: captured value - our piece value (if position is attacked)
            int score;
            int plus = pieceValue(move.getCap()->getType());
            int minus = pieceValue(p->getType());
            score = plus;
            if (b.isAttacked(move.getTo(), (colour == 'w' ? 'b' : 'w'))) {
                score -= minus;
            }
            // Update if evaluation is better than scored position
            if (score > max_score) {
                max_score = score;
                bestMove = move;
            }
        }
    }
    if (max_score >= 0) {
        return bestMove;
    } else {
        return random;
    }
}

Move ComputerPlayer::cMove(Board& b) { 
    switch (level) { 
        case 1: return lv1Move(b, colour);
        case 2: return lv2Move(b, colour);
        case 3: return lv3Move(b, colour);
        case 4: return lv4Move(b, colour);
    }
}

