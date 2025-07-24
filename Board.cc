#include "Board.h"

#define BOARD_SIZE 64

const std::vector<char> preset {
    'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', // row 8
    'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
    '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0',
    '0', '0', '0', '0', '0', '0', '0', '0',
    'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
    'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', // row 1
};

Board::Board() : graphicDisplay (550, 550) { 
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
            //Handle terminal display
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

void Board::initGraphics() {

    const int padding = 25;
    int windowHeight = graphicDisplay.getHeight();
    int windowWidth = graphicDisplay.getWidth();
    const int boardSize = windowHeight - 2 * padding; //size of board
    int tileWidth = boardSize / 8;
    int tileHeight = boardSize / 8;

    graphicDisplay.fillRectangle(0, 0, windowWidth, windowHeight, 7);

    for (int i = 0; i < 8; i++) {

        //Side numbers
        std::string num = std::to_string(8 - i);
        graphicDisplay.drawString(padding / 2, padding + tileHeight * i + tileHeight / 2, num);

        //Setup initial tiles
        for (int j = 0; j < 8; j++) {
            //Handle black / white tiles
            if ((i + j) % 2 == 0) graphicDisplay.fillRectangle(padding + tileWidth * j, padding + tileHeight * i, tileWidth, tileHeight, 6);
            else graphicDisplay.fillRectangle(padding + tileWidth * j, padding + tileHeight * i, tileWidth, tileHeight, 5);
            if (displayGrid[i * 8 + j] != '0') {
                std::string s {displayGrid[i * 8 + j]};
                graphicDisplay.drawString(padding + tileWidth * j + tileWidth / 2, padding + tileHeight * i + tileHeight / 2, s);
            }
        }

    }

    //Draw bottom letters
    for (char c = 'a'; c <= 'h'; c++){
        std::string s {c};
        graphicDisplay.drawString(padding + tileWidth * (c - 'a') + tileWidth / 2, windowHeight - padding / 2, s);
    }

}

std::stack<Move>& Board::getHistory() {
    return history;
}

Position Board::getWhiteKing() {
    return white_king;
}

void Board::setWhiteKing(Position p) {
    white_king = p;
}

Position Board::getBlackKing() {
    return black_king;
}

void Board::setBlackKing(Position p) {
    black_king = p;
}

void Board::drawTile(Position pos, char piece) {

    const int padding = 25;
    int windowHeight = graphicDisplay.getHeight();
    int windowWidth = graphicDisplay.getWidth();
    const int boardSize = windowHeight - 2 * padding; //size of board
    int tileWidth = boardSize / 8;
    int tileHeight = boardSize / 8;

    int i = pos.getRow();
    int j = pos.getCol();
    if ((i + j) % 2 == 0) graphicDisplay.fillRectangle(padding + tileWidth * j, padding + tileHeight * i, tileWidth, tileHeight, 6);
    else graphicDisplay.fillRectangle(padding + tileWidth * j, padding + tileHeight * i, tileWidth, tileHeight, 5);

    if (piece != '0'){
        std::string s {piece};
        graphicDisplay.drawString(padding + tileWidth * j + tileWidth / 2, padding + tileHeight * i + tileHeight / 2, s);
    }


}

bool inLegalMoves(const Move m, Piece* p) { 
    //std::cout << p->getType() << '\n';
    std::vector<Move> legalMoves = p->getLegalMoves();
    for (int i = 0; i < (int) legalMoves.size(); ++i) {
        std::cout << legalMoves[i] << '\n';
        if (m == legalMoves[i]) return true;
    }
    return false;
}

bool Board::makeMove(Move m) {

    //Leave if not legal
    if (!inLegalMoves(m, getPieceAt(m.getFrom()))) {
        std::cout << "Not a valid move.\n";
        return false;
    }

    // En passant
    // Note: if a valid capturing pawn move lands in empty, then en passant
    if (m.getPieceMoved()->getType() == 'p'
    && m.getFrom().getCol() != m.getTo().getCol()
    && !m.getCap()
    && getDisplayGrid()[m.getTo().to1D()] == '0') {
        
        // Find and remove captured pawn not on landing square
        Position capturedP(m.getTo().getCol(), m.getFrom().getRow());
        if (Piece* captured = getPieceAt(capturedP)) {
            for (auto it = grid.begin(); it != grid.end(); ++it) {
                if (it->get() == captured) {
                    grid.erase(it);
                    break;
                }
            }
            // Update display
            displayGrid[capturedP.to1D()] = '0';
            drawTile(capturedP);
        }
    }

    //Update piece info
    m.getPieceMoved()->modPos(m.getTo());
    displayGrid[m.getTo().to1D()] = displayGrid[m.getFrom().to1D()];
    drawTile(m.getTo(), displayGrid[m.getTo().to1D()]);

    // Remove captured piece (if any)
    if (m.getCap()) {
        auto it = grid.begin();
        for (; it != grid.end(); it++){
            if (it->get() == m.getCap()){
                break;
            }
        }
        grid.erase(it);
    }

    if (m.getPieceMoved()->getType() == 'k' && abs(m.getFrom().getCol() - m.getTo().getCol()) > 1) {  // castling
        Position oldPos = {0, 0};
        Position newPos = {0, 0};
        if (m.getTo().getCol() > m.getFrom().getCol()) {  // king side castle
            newPos = {m.getTo().getCol() - 1, m.getTo().getRow()};
            oldPos = {m.getTo().getCol() + 1, m.getTo().getRow()};
        }
        else { // queen side castle
            newPos = {m.getTo().getCol() + 1, m.getTo().getRow()};
            oldPos = {m.getTo().getCol() - 2, m.getTo().getRow()};
        }

        std::cout << oldPos << " " << newPos << std::endl;

        Piece* r = getPieceAt(oldPos);

        r->modPos(newPos);
        r->setMoved();
        displayGrid[newPos.to1D()] = displayGrid[oldPos.to1D()];
        displayGrid[oldPos.to1D()] = '0';
        drawTile(newPos, displayGrid[newPos.to1D()]);
        drawTile(oldPos);
    }

    // 4) Handle promotion
    if (m.getPromoType() != '0') {

        char colour = m.getPieceMoved()->getColour();
        std::cout << colour << '\n';
        Position pos = m.getTo();

        //Erase original piece
        auto it = grid.begin();
        for (; it != grid.end(); it++){
            if (it->get() == m.getPieceMoved()){
                break;
            }
        }
        grid.erase(it);

        // Create a new unique_ptr
        std::unique_ptr<Piece> newPiece;
        switch (m.getPromoType()) {
            case 'N': newPiece = std::make_unique<Knight>(colour, pos, this); break;
            case 'B': newPiece = std::make_unique<Bishop>(colour, pos, this); break;
            case 'R': newPiece = std::make_unique<Rook>(colour, pos, this);   break;
            case 'Q': newPiece = std::make_unique<Queen>(colour, pos, this);  break;
        }
        grid.emplace_back(std::move(newPiece));
        displayGrid[pos.to1D()] = (colour=='b' ? tolower(m.getPromoType()) : toupper(m.getPromoType()));
        drawTile(pos, displayGrid[pos.to1D()]);

    }

    // Clear the origin square
    displayGrid[m.getFrom().to1D()] = '0';
    drawTile(m.getFrom()); //draw over old square
    m.getPieceMoved()->setMoved();

    // record Position of the kings
    if (m.getPieceMoved()->getType() == 'K') {
        setWhiteKing(m.getTo());
    }
    if (m.getPieceMoved()->getType() == 'k') {
        setBlackKing(m.getTo());
    }

    // record move in history
    history.push(m);
    return true;

}

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
    int dir = (enemy_colour == 'b') ? -1 : 1;
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

int Board::isCheckStalemate(char colour) {
    Position kingPos = (colour == 'w') ? getWhiteKing() : getBlackKing();
    bool inCheck = isAttacked(kingPos, (colour == 'w') ? 'b' : 'w');
    for (const auto& piece : grid) {
        if (piece->getColour() == colour && piece->getLegalMoves().size() != 0) {
            std::cout << piece->getLegalMoves()[0] << std::endl;
            return 0;  // Has legal moves: neither condition
        }
    }
    // No legal moves found
    return inCheck ? 2 : 1;  // 2 if checkmate, 1 if stalemate
}
