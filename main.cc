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

    Game G; 

    char fCol, tCol;
    int fRow, tRow;

    //Read whole line
    std::string line;
    while (std::getline(std::cin, line)){
        std::istringstream iss {line};
        //Read the first word of the line, the command
        std::string cmd;
        iss >> cmd;
        if (cmd == "game") {
            std::string player1 = "", player2 = "";
            iss >> player1 >> player2;
            if (player1 == "human") {
                if (player2 == "human"){
                    G.startGame();
                }
            }
            else{
                
            }
        }
        else if (cmd == "move"){
            if (G.gameOn()){
                iss >> fCol >> fRow >> tCol >> tRow;
                //For pawn promotion
                char promo = '0';
                iss >> promo;
                G.makeMove(fCol, fRow, tCol, tRow, promo);
            }
            else std::cout << "No active game. Please start a game using \"game <whiteplayer> <blackplayer>\"" << std::endl;
        }
        else if (cmd == "setup"){
            if (G.gameOn()){
                std::cout << "Error: A game is currently active, please finish the game first" << std::endl;
            }
            else G.setup();
        }
        //Invalid commands
        else{
            std::cout << "Unrecognized command: " << cmd << std::endl;
        }

        G.display();

    }

    return 0;

}
