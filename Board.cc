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

        displayGrid.push_back( preset[i] );

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

/*
void Board::display() {
  for (int r = 0; r < 8; ++r) {
    std::cout << 8 - r << " ";
    for (int c = 0; c < 8; ++c) {
      bool found = false;

      for (const auto &piece : grid) {

        if (piece->getPosition().getRow() == r && piece->getPosition().getCol() == c) {
            char c = piece->getType();

            if (piece->getColour() == 'b') std::cout << std::toupper(c) << ' ';
            else std::cout << c << ' ';

            found = true;
            break;
        }

      }
      if (!found) std::cout << ((r + c) % 2 == 0 ? ' ' : '_') << ' ';
    }

    std::cout << std::endl;
  }
}
*/

void Board::display() {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (displayGrid[i * 8 + j] == '0'){
                std::cout << ((i + j) % 2 == 0 ? ' ' : '_') << ' ';
            }
            else{
                std::cout << displayGrid[i * 8 + j];
            }
        }
        std::cout << '\n';
    }

}
