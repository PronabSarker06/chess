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

    std::cout << "Welcome to Chess :D" << std::endl;

    int whiteScore = 0, blackScore = 0;

    //Wrap in outer loop to reinstantiate Game after it completes
    while (true) {

        Game G; 

        char fCol, tCol;
        int fRow, tRow;

        std::cout << "Current Score" << std::endl;
        std::cout << "White: " << whiteScore << std::endl;
        std::cout << "Black: " << blackScore << std::endl;

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
                    int condition = G.getBoard().isCheckStalemate(G.getTurn());
                    if (condition) {
                        if (condition == 2) {
                            // checkmate
                            if (G.getTurn() == 'w') blackScore++;
                            else whiteScore++;
                            break;
                        } else if (condition == 1) {
                            // stalemate: draw
                            blackScore += 0.5;
                            whiteScore += 0.5;
                            break;
                        }
                    }
                }
                else std::cout << "No active game. Please start a game using \"game <whiteplayer> <blackplayer>\"" << std::endl;
            }
            else if (cmd == "setup"){
                if (G.gameOn()){
                    std::cout << "Error: A game is currently active, please finish the game first" << std::endl;
                }
                else G.setup();
            }
            else if (cmd == "resign"){
                if (G.getTurn() == 'w') blackScore++;
                else whiteScore++;
                break;
            }
            //Invalid commands
            else{
                std::cout << "Unrecognized command: " << cmd << std::endl;
            }

            G.display();

        }

        //If no more input
        if (std::cin.eof()){
            break;
        }

    }

    std::cout << "Final Score" << std::endl;
    std::cout << "White: " << whiteScore << std::endl;
    std::cout << "Black: " << blackScore << std::endl;

    return 0;

}
