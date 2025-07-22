#include "Piece.h"
#include "Move.h"
#include "Position.h"
#include "Board.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "Game.h"
#include <iostream>
#include <sstream>
#include <algorithm>

int main () {

    std::cout << "Welcome to Chess :D\n";

    Board B;
    B.display();
    B.initGraphics();
    char fCol, tCol;
    int fRow, tRow;
    char whose_turn = 'w';

    //Read whole line
    std::string line;
    while (std::getline(std::cin, line)){
        std::istringstream iss {line};
        //Read the first word of the line, the command
        std::string cmd;
        iss >> cmd;
        if (cmd == "move"){
            iss >> fCol >> fRow >> tCol >> tRow;
            //For pawn promotion
            char promo = '0';
            iss >> promo;
            std::cout << promo << '\n';
            //Make 0 indexing
            fRow--;
            tRow--;
            //Create pos
            Position f = {fCol - 'a', 7 - fRow};
            Position t = {tCol - 'a', 7 - tRow};
            Piece* p = B.getPieceAt(f);
            //Handle turn
            if (p == nullptr) {
                std::cout << "No piece located there." << std::endl;
            } else if (p->getColour() != whose_turn) {
                std::cout << "Cannot move your enemy's pieces." << std::endl;
            } else if (B.makeMove({f, t, p, B.getPieceAt(t), promo})){
                if (whose_turn == 'w') {
                    whose_turn = 'b';
                } else {
                    whose_turn = 'w';
                }
            }
        }
        //Invalid commands
        else{
            std::cout << "Unrecognized command: " << cmd << std::endl;
        }

        B.display();

    }

    return 0;

}
