#include "Board.h"

#define BOARD_SIZE 64

const char preset[BOARD_SIZE] {
    'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', // row 1
    'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
    '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0',
    'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
    'R', 'N', 'B', 'K', 'Q', 'B', 'N', 'R', // row 8
};

Board::Board() { 
    for (int i = 0; i < BOARD_SIZE; ++i) {

        displayGrid.push_back( preset[i] );

        if (preset[i] == '0') { 
            continue;
        }
        else if (preset[i] == 'p' || preset[i] == 'P') { 
            grid.push_back(std::make_unique<Pawn>((preset[i] == 'p' ? 'w' : 'b'), Position{i/8, i%8}, this));
        }
        else if (preset[i] == 'n' || preset[i] == 'N') { 
            grid.push_back(std::make_unique<Knight>((preset[i] == 'n' ? 'w' : 'b'), Position{i/8, i%8}, this));
        }
        else if (preset[i] == 'b' || preset[i] == 'B') { 
            grid.push_back(std::make_unique<Bishop>((preset[i] == 'b' ? 'w' : 'b'), Position{i/8, i%8}, this));
        }
        else if (preset[i] == 'r' || preset[i] == 'R') { 
            grid.push_back(std::make_unique<Rook>((preset[i] == 'r' ? 'w' : 'b'), Position{i/8, i%8}, this));
        }
        else if (preset[i] == 'q' || preset[i] == 'Q') { 
            grid.push_back(std::make_unique<Queen>((preset[i] == 'q' ? 'w' : 'b'), Position{i/8, i%8}, this));
        }
        else { 
            grid.push_back(std::make_unique<King>((preset[i] == 'k' ? 'w' : 'b'), Position{i/8, i%8}, this));
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
            else {
                std::cout << displayGrid[i * 8 + j] << ' ';
            }
        }
        std::cout << '\n';
    }

}
