#include "Game.h"
#include "Setup.h"
#include <sstream>
#include <iostream>
#include <vector>

const std::vector<char> validPieces = {'p', 'n', 'b', 'q', 'k', 'r'};

Game::Game() : whoseTurn{'w'}, board{}, moveHistory{} {
    board.initGraphics(); //init X11
}

bool validPiece (char p) {
    for (auto& c : validPieces) if (c == p) return true;
    return false;
}

void Game::setup() {

    Setup S {&board};

    std::string line;

    while (getline(std::cin, line)) {
        std::istringstream iss {line};
        std::string cmd;
        iss >> cmd;
        if (cmd == "+"){
            char piece, col;
            int row;
            iss >> piece >> col >> row;
            Position pos {col - 'a', 8 - row};
            if (pos.valid()){
                if (validPiece(std::tolower(piece))){
                    if (piece >= 'a') S.addPiece(pos, 'b', std::tolower(piece));
                    else S.addPiece(pos, 'w', std::tolower(piece));
                }
                else{
                    std::cout << "Not a valid piece" << std::endl;
                }
            }
            else{
                std::cout << "Invalid position" << std::endl;
            }
        }
        else if (cmd == "-"){
            char col;
            int row;
            iss >> col >> row;
            Position pos {col - 'a', 8 - row};
            std::cout << pos << '\n';
            if (pos.valid()){
                S.removePiece(pos);
            }
            else{
                std::cout << "Invalid position" << std::endl;
            }
        }
        else if (cmd == "="){
            std::string colour;
            iss >> colour;
            if (colour == "black") whoseTurn = 'b';
            else if (colour == "white") whoseTurn = 'w';
            else std::cout << "Not a valid colour" << std::endl;
        }
        else if (cmd == "done"){
            if (true) break;
        }
        else{
            std::cout << "Error, please enter a valid command" << std::endl;
        }
    }

}

void Game::makeMove(char fCol, char fRow, char tCol, char tRow, char promo) {
    //Make 0 indexing
    fRow--;
    tRow--;
    //Create pos
    Position f = {fCol - 'a', 7 - fRow};
    Position t = {tCol - 'a', 7 - tRow};

    if (!f.valid() || !t.valid()){
        std::cout << "Invalid position(s) entered" << std::endl;
        return;
    } 

    Piece* p = board.getPieceAt(f);

    //Handle turn
    //No piece
    if (p == nullptr) {
        std::cout << "No piece located there." << std::endl;
    } else if (p->getColour() != whoseTurn) {
        std::cout << "Cannot move your enemy's pieces." << std::endl;
    } else if (board.makeMove({f, t, p, board.getPieceAt(t), promo})){
        flipTurn();
    }
}

void Game::display() {
    board.display();
}

bool Game::gameOn() {
    return gameActive;
}

void Game::startGame() {
    if (gameActive){
        std::cout << "Game is already active" << std::endl;
    }
    else gameActive = true;
}

char Game::getTurn() {
    return whoseTurn;
}

Board* Game::getBoard() {
    return &board;
}

void Game::flipTurn() {
    if (whoseTurn == 'w') {
        whoseTurn = 'b';
    } else {
        whoseTurn = 'w';
    }
}
