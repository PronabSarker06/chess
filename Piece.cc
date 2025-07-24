#include "Piece.h"
#include "Move.h"
#include "Board.h"

Piece::Piece(char c, char t, Position p, Board* bptr)
    : colour{c}, type{t}, hasMoved{false}, position{p}, bptr {bptr} {}

bool Piece::operator==(const Piece& o) { 
    return (colour == o.colour && type == o.type && hasMoved == o.hasMoved && position == o.position && bptr == o.bptr);
}

Position Piece::getPosition() { 
    return this->position;
}

void Piece::setMoved() { 
    hasMoved = true;
}

char Piece::getType() { 
    return this->type;
}

char Piece::getColour() { 
    return this->colour;
}

void Piece::modPos(Position p) { 
    this->position = p;
}

bool Piece::getHasMoved() { 
    return this->hasMoved;
}

char pColour (char p) {
    return std::isupper(p) ? 'w' : 'b';
}

bool charAttack (Position square, std::vector<char>& grid) {

    char enemy_colour = std::isupper(grid[square.to1D()]) ? 'b' : 'w';

    // Check if enemy knights are attacking the square
    std::vector<int> col_change = {2, 2, -2, -2, 1, 1, -1, -1};
    std::vector<int> row_change = {1, -1, 1, -1, 2, -2, 2, -2};

    for (int i = 0; i < 8; ++i) {
        Position to = {
            square.getCol() + col_change[i],
            square.getRow() + row_change[i]
        };
        if (to.valid()) {
            char p = grid[to.to1D()];
            //Piece* p = getPieceAt(to);
            if (p != '0' && pColour(p) == enemy_colour) {
                char type = p;
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
                char p = grid[to.to1D()];
                if (p == '0') continue; 
                if (pColour(p) == enemy_colour) {
                    char type = p;
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
    int dir = (enemy_colour == 'b') ? -1 : 1;
    Position pawns[2] = {
        {square.getCol() - 1, square.getRow() + dir},
        {square.getCol() + 1, square.getRow() + dir}
    };
    for (Position pos : pawns) {
        if (pos.valid()) {
            if (grid[pos.to1D()] != '0' && pColour(grid[pos.to1D()]) == enemy_colour) {
                if ((enemy_colour == 'w' && grid[pos.to1D()] == 'P')
                || (enemy_colour == 'b' && grid[pos.to1D()] == 'p')) {
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
                char p = grid[to.to1D()];
                if (p != '0' && pColour(p) == enemy_colour) {
                    if ((p == 'K') || (p == 'k')) {
                        return true;
                    }
                }
            }
        }
    }
    return false;

}

bool Piece::kingSafe(Move m){

    std::vector<char> cpy = bptr->getDisplayGrid();

    cpy[m.getTo().to1D()] = cpy[m.getFrom().to1D()];
    cpy[m.getFrom().to1D()] = '0';

    Position king{0,0};
    char colour = m.getPieceMoved()->getColour();

    for (int i = 0; i < 64; ++i) { 
        if (colour == 'b' && cpy[i] == 'k') king = Position{i%8, i/8};
        if (colour == 'w' && cpy[i] == 'K') king = Position{i%8, i/8};
    }

    //std::cout << "King: " << king << " and Kingsafe: " << !charAttack(king, cpy) << "and "<< m << '\n';

    return !charAttack(king, cpy);

}
