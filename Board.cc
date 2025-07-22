#include "Board.h"

#define BOARD_SIZE 64

const char preset[BOARD_SIZE] {
    'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', // row 8
    'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
    '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0',
    'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
    'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', // row 1
};

Board::Board() { 
    for (int i = 0; i < BOARD_SIZE; ++i) {

        displayGrid.push_back( preset[i] );

        if (preset[i] == '0') { 
            continue;
        }
        else if (preset[i] == 'p' || preset[i] == 'P') { 
            grid.push_back(std::make_unique<Pawn>((preset[i] == 'p' ? 'b' : 'w'), Position{i%8, i/8}, this));
        }
        else if (preset[i] == 'n' || preset[i] == 'N') { 
            grid.push_back(std::make_unique<Knight>((preset[i] == 'n' ? 'b' : 'w'), Position{i%8, i/8}, this));
        }
        else if (preset[i] == 'b' || preset[i] == 'B') { 
            grid.push_back(std::make_unique<Bishop>((preset[i] == 'b' ? 'b' : 'w'), Position{i%8, i/8}, this));
        }
        else if (preset[i] == 'r' || preset[i] == 'R') { 
            grid.push_back(std::make_unique<Rook>((preset[i] == 'r' ? 'b' : 'w'), Position{i%8, i/8}, this));
        }
        else if (preset[i] == 'q' || preset[i] == 'Q') { 
            grid.push_back(std::make_unique<Queen>((preset[i] == 'q' ? 'b' : 'w'), Position{i%8, i/8}, this));
        }
        else { 
            grid.push_back(std::make_unique<King>((preset[i] == 'k' ? 'b' : 'w'), Position{i%8, i/8}, this));
        }
    }
}

void Board::display() {

    for (int i = 0; i < 8; i++) {

        std::cout << 8 - i << ' '; //side numbers

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

    std::cout << "  ";
    for (char c = 'a'; c <= 'h'; c++){
        std::cout << c << ' ';
    } std::cout << std::endl;

}

bool inLegalMoves(const Move m, Piece* p) { 
    std::vector<Move> legalMoves = p->getLegalMoves();
    for (int i = 0; i < (int) legalMoves.size(); ++i) {
        if (m == legalMoves[i]) return true;
    }
    return false;
}

bool Board::makeMove(Move m) {

    if (inLegalMoves(m, getPieceAt(m.getFrom()))) {
      for (auto &piece : grid) {
        if (piece.get() == m.getPieceMoved()) {
            piece.get()->modPos(m.getTo()); // do not touch, mystical

            if (m.getCap()) { 
                // Remove captured piece from grid
                for (auto it = grid.begin(); it != grid.end(); ++it) {
                    if (it->get() == m.getCap()) {
                        grid.erase(it);
                        break;
                    }
                }
            }

            if (m.getPieceMoved()->getType() == 'k' && !m.getPieceMoved()->getHasMoved()) { //segfault 
                Position oldPos = {0, 0};
                Position newPos = {0, 0};
                if (m.getFrom().getRow() - m.getTo().getRow() == 2) {  // king
                    newPos = {m.getTo().getCol() + 1, m.getTo().getRow()};
                    oldPos = {m.getTo().getCol() - 1, m.getTo().getRow()};
                }
                else { // queen
                    newPos = {m.getTo().getCol() + 1, m.getTo().getRow()};
                    oldPos = {m.getTo().getCol() - 2, m.getTo().getRow()};
                }

                std::cout << oldPos << " " << newPos << std::endl;

                Piece* r = getPieceAt(oldPos);

                r->modPos(newPos);
                r->setMoved();
                displayGrid[newPos.to1D()] = displayGrid[oldPos.to1D()];
                displayGrid[oldPos.to1D()] = '0';
            } 

            if (m.getPromoType() != '0') { 

                // Promote the pawn
                char colour = piece->getColour();
                Position pos = m.getTo();

                if (m.getPromoType() == 'N') {
                    grid.push_back(std::make_unique<Knight>(colour, pos, this));
                    displayGrid[pos.to1D()] = (colour == 'w' ? 'n' : 'N');
                } else if (m.getPromoType() == 'B') {
                    grid.push_back(std::make_unique<Bishop>(colour, pos, this));
                    displayGrid[pos.to1D()] = (colour == 'w' ? 'b' : 'B');
                } else if (m.getPromoType() == 'R') {
                    grid.push_back(std::make_unique<Rook>(colour, pos, this));
                    displayGrid[pos.to1D()] = (colour == 'w' ? 'r' : 'R');
                } else if (m.getPromoType() == 'Q') {
                    grid.push_back(std::make_unique<Queen>(colour, pos, this));
                    displayGrid[pos.to1D()] = (colour == 'w' ? 'q' : 'Q');
                }

                for (auto it = grid.begin(); it != grid.end(); ++it) { // kill the pawn
                    if (it->get() == piece.get()) {
                        grid.erase(it);
                        break;
                    }
                }
            }
            else{
                displayGrid[m.getTo().to1D()] = displayGrid[m.getFrom().to1D()];
            }
            
            piece->setMoved();

            displayGrid[m.getFrom().to1D()] = '0';
            
            return true;
            
        }
      }
    }
    else { 
        std::cout << "Not a valid move." << std::endl;
        return false;
    }

}

/*void Board::castle(King &k, Rook &r) {
    if (k.getColour() == 'b') {
        if (r.getPosition().getCol() == 7) {
            // King Side
            // Move pieces
            grid[7 * 8 + 6] = std::move(grid[7 * 8 + 4]);
            grid[7 * 8 + 5] = std::move(grid[7 * 8 + 7]);
            // Positions update
            grid[7 * 8 + 6]->modPos(Position{6, 7});
            grid[7 * 8 + 5]->modPos(Position{5, 7});
            // Set moved flags
            grid[7 * 8 + 6]->setMoved();
            grid[7 * 8 + 5]->setMoved();
        } else if (r.getPosition().getCol() == 0) {
            // Queen Side
            grid[7 * 8 + 2] = std::move(grid[7 * 8 + 4]);
            grid[7 * 8 + 3] = std::move(grid[7 * 8 + 0]);
            grid[7 * 8 + 2]->modPos(Position{2, 7});
            grid[7 * 8 + 3]->modPos(Position{3, 7});
            grid[7 * 8 + 2]->setMoved();
            grid[7 * 8 + 3]->setMoved();
        }
    } else if (k.getColour() == 'w') {
        if (r.getPosition().getCol() == 7) {
            // King Side
            grid[0 * 8 + 6] = std::move(grid[0 * 8 + 4]);
            grid[0 * 8 + 5] = std::move(grid[0 * 8 + 7]);
            grid[0 * 8 + 6]->modPos(Position{6, 0});
            grid[0 * 8 + 5]->modPos(Position{5, 0});
            grid[0 * 8 + 6]->setMoved();
            grid[0 * 8 + 5]->setMoved();
        } else if (r.getPosition().getCol() == 0) {
            // Queen Side
            grid[0 * 8 + 2] = std::move(grid[0 * 8 + 4]);
            grid[0 * 8 + 3] = std::move(grid[0 * 8 + 0]);
            grid[0 * 8 + 2]->modPos(Position{2, 0});
            grid[0 * 8 + 3]->modPos(Position{3, 0});
            grid[0 * 8 + 2]->setMoved();
            grid[0 * 8 + 3]->setMoved();
        }
    }
}
*/

bool Board::isAttacked(Position square, char enemy_colour) {
    // Check if enemy knights are attacking the square
    std::vector<int> col_change = {2, 2, -2, -2, 1, 1, -1, -1};
    std::vector<int> row_change = {1, -1, 1, -1, 2, -2, 2, -2};
    for (int i = 0; i < 8; ++i) {
        Position to = {
            square.getCol() + col_change[i],
            square.getRow() + row_change[i]
        };
        if (to.valid()) {
            Piece* p = getPieceAt(to);
            if (p && p->getColour() == enemy_colour) {
                char type = p->getType();
                if ((enemy_colour == 'w' && type == 'N')
                || (enemy_colour == 'b' && type == 'n')) {
                    return true;
                }
            }
        }
    }

    // Check long range attacks (queen/rook/bishop)
    for (int row_change = -1; row_change < 2; ++row_change) {
        for (int col_change = -1; col_change < 2; ++col_change) {
            if (row_change == 0 && col_change == 0) {
                continue;
            }
            Position to = square;
            // Loop in one direction until hit obstacle (own piece, out of bounds)
            while (true) {
                to = {to.getCol() + col_change, to.getRow() + row_change};
                if (!to.valid()) break;
                Piece* p = getPieceAt(to);
                if (!p) continue; 
                if (p->getColour() == enemy_colour) {
                    char type = p->getType();
                    bool isDiagonal = (abs(row_change) == abs(col_change));
                    if (enemy_colour == 'w') {
                        if ((isDiagonal && (type == 'B' || type == 'Q'))
                        || (!isDiagonal && (type == 'R' || type == 'Q'))) {
                            return true;
                        }
                    } else {
                        if ((isDiagonal && (type == 'b' || type == 'q'))
                        || (!isDiagonal && (type == 'r' || type == 'q'))) {
                            return true;
                        }
                    }
                }
                break;
            }
        }
    }
    // Check pawn attacks
    int dir = (enemy_colour == 'w') ? -1 : 1;
    Position pawns[2] = {
        {square.getCol() - 1, square.getRow() + dir},
        {square.getCol() + 1, square.getRow() + dir}
    };
    for (Position p : pawns) {
        if (p.valid()) {
            if (getPieceAt(p) && getPieceAt(p)->getColour() == enemy_colour) {
                if ((enemy_colour == 'w' && getPieceAt(p)->getType() == 'P')
                || (enemy_colour == 'b' && getPieceAt(p)->getType() == 'p')) {
                    return true;
                }
            }
        }
    }

    // Check enemy king attack
    for (int col_change = -1; col_change < 2; ++col_change) {
        for (int row_change = -1; row_change < 2; ++row_change) {
            if (row_change == 0 && col_change == 0) {
                continue;
            }
            Position to = {
                square.getCol() + col_change,
                square.getRow() + row_change
            };
            if (to.valid()) {
                Piece* p = getPieceAt(to);
                if (p && p->getColour() == enemy_colour) {
                    if ((p->getType() == 'K') || (p->getType() == 'k')) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

Piece* Board::getPieceAt(const Position pos) {
    for (const auto& piece : grid) {
        //std::cout << piece.get()->getPosition() << ' ' << pos << '\n';
        if (piece.get()->getPosition() == pos) {
            return piece.get(); 
        }
    }
    return nullptr; 
}

std::vector<char>& Board::getDisplayGrid() {
    return displayGrid;
}

bool Board::isCheckmate (char colour) {

    char target = colour == 'b' ? 'k' : 'K';
    Piece* king = nullptr;

    //Find where king is on board
    for (int i = 0; i < 64; i++) {
        if (displayGrid[i] == target){
            king = getPieceAt(Position{i % 8, i / 8});
        }
    }

    return false;

}
