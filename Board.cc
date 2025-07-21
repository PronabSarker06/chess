#include "Board.h"

#define BOARD_SIZE 64

const char preset[BOARD_SIZE] {
    'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', // row 1
    'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
    '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0',
    'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
    'r', 'n', 'b', 'k', 'q', 'b', 'n', 'r', // row 8
};

Board::Board() { 
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (preset[i] == '0') { 
            continue;
        }
        else if (preset[i] == 'p') { 
            grid.push_back(std::make_unique<Pawn>((i < 16 ? 'w' : 'b'), Position{i/8, i%8}));
        }
        else if (preset[i] == 'n') { 
            grid.push_back(std::make_unique<Knight>((i < 16 ? 'w' : 'b'), Position{i/8, i%8}));
        }
        else if (preset[i] == 'b') { 
            grid.push_back(std::make_unique<Bishop>((i < 16 ? 'w' : 'b'), Position{i/8, i%8}));
        }
        else if (preset[i] == 'r') { 
            grid.push_back(std::make_unique<Rook>((i < 16 ? 'w' : 'b'), Position{i/8, i%8}));
        }
        else if (preset[i] == 'q') { 
            grid.push_back(std::make_unique<Queen>((i < 16 ? 'w' : 'b'), Position{i/8, i%8}));
        }
        else { 
            grid.push_back(std::make_unique<King>((i < 16 ? 'w' : 'b'), Position{i/8, i%8}));
        }
    }
}

void Board::display() { 
    for (int i = 0; i < BOARD_SIZE; ++i) { 
        
    }
}