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
#include "ComputerPlayer.h"
#include <iostream>
#include <sstream>
#include <algorithm>

enum PLAYERTYPE {HUMAN, COMP};

const int FAIL = -1;

//Read in player given cmd s
//returns -1 for failed read
//0 = human
//1, 2, 3, 4 for computer level
int readPlayer (std::string& s, PLAYERTYPE& player, ComputerPlayer& compPlayer, char colour) {
    if (s == "human") {
        player = PLAYERTYPE::HUMAN;
        return 0;
    }
    else{
        std::istringstream iss {s};
        std::string firstPart = "";
        int lettersRead = 0;
        int level;
        char c;
        //Ensure the string starts with "computer"
        while (lettersRead < 8 && iss >> c){
            firstPart += c;
            lettersRead++;
        }
        iss >> level; //Read level
        //std::cout << firstPart << ' ' << level << '\n';
        if (firstPart == "computer" && 1 <= level && level <= 4){
            player = PLAYERTYPE::COMP;
            compPlayer = ComputerPlayer (level, colour);
            return level;
        }
        return FAIL;
    }
} 

void scoreUpdate(int condition, int& whiteScore, int& blackScore, Game& G) {
    //std::cout << "condition: " << condition << '\n';
    if (condition) {
        if (condition == 2) {
            // checkmate
            if (G.getTurn() == 'w') blackScore++;
            else whiteScore++;
        } else if (condition == 1) {
            // stalemate: draw
            blackScore += 0.5;
            whiteScore += 0.5;
        }
    }
}

int main () {

    std::cout << "Welcome to Chess :D" << std::endl;

    int whiteScore = 0, blackScore = 0;
    PLAYERTYPE white = PLAYERTYPE::HUMAN;
    PLAYERTYPE black = PLAYERTYPE::HUMAN;
    ComputerPlayer whiteComp (1, 'w'), blackComp (1, 'b');

    //Wrap in outer loop to reinstantiate Game after it completes
    while (true) {

        Game G; 

        char fCol, tCol;
        int fRow, tRow;

        //std::cout << "Current Score" << std::endl;
        //std::cout << "White: " << whiteScore << std::endl;
        //std::cout << "Black: " << blackScore << std::endl;

        //Read whole line
        std::string line;
        while (white == PLAYERTYPE::HUMAN || black == PLAYERTYPE::HUMAN){

            if (G.gameOn() && white == PLAYERTYPE::COMP && G.getTurn() == 'w'){
                G.getBoard().makeMove(whiteComp.cMove(G.getBoard()));
                G.display();
                G.flipTurn();
                bool inCheck = false;
                int condition = G.getBoard().isCheckStalemate(G.getTurn(), inCheck);
                if (inCheck && condition == 0) {
                    std::cout << ((G.getTurn() == 'w') ? "White" : "Black") << " is in check." << std::endl;
                }
                scoreUpdate(condition, whiteScore, blackScore, G);
                if (condition != 0) break;
            }
            if (G.gameOn() && black == PLAYERTYPE::COMP && G.getTurn() == 'b') {
                G.getBoard().makeMove(blackComp.cMove(G.getBoard()));
                G.display();
                G.flipTurn();
                bool inCheck = false;
                int condition = G.getBoard().isCheckStalemate(G.getTurn(), inCheck);
                if (inCheck && condition == 0) {
                    std::cout << ((G.getTurn() == 'w') ? "White" : "Black") << " is in check." << std::endl;
                }
                scoreUpdate(condition, whiteScore, blackScore, G);
                if (condition != 0) break;
            }

            if (!std::getline(std::cin, line)) break; //EOF
            std::istringstream iss {line};
            //Read the first word of the line, the command
            std::string cmd;
            iss >> cmd;
            if (cmd == "game") {
                std::string player1 = "", player2 = "";
                iss >> player1 >> player2;
                if (readPlayer(player1, white, whiteComp, 'w') == FAIL) std::cout << "Invalid white player" << std::endl;
                else if (readPlayer(player2, black, blackComp, 'b') == FAIL) std::cout << "Invalid black player" << std::endl;
                else G.startGame();
            }
            else if (cmd == "move"){
                if (G.gameOn()){
                    iss >> fCol >> fRow >> tCol >> tRow;
                    //For pawn promotion
                    char promo = '0';
                    iss >> promo;
                    G.makeMove(fCol, fRow, tCol, tRow, promo);
                    //std::cout << G.getTurn() << "'s turn \n";
                    bool inCheck = false;
                    int condition = G.getBoard().isCheckStalemate(G.getTurn(), inCheck);
                    if (inCheck && condition == 0) {
                        std::cout << ((G.getTurn() == 'w') ? "White" : "Black") << " is in check." << std::endl;
                    }
                    scoreUpdate(condition, whiteScore, blackScore, G);
                    if (condition != 0) break;
                }
                else std::cout << "No active game. Please start a game using \"game <whiteplayer> <blackplayer>\"" << std::endl;
            }
            else if (cmd == "setup"){
                if (G.gameOn()){
                    std::cout << "Error: A game is currently active, please finish the game first" << std::endl;
                }
                else{
                    std::cout << "Setup mode entered, please enter setup commands!" << std::endl;
                    G.setup();
                }
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

        //Two computer players fight
        if (white == PLAYERTYPE::COMP && black == PLAYERTYPE::COMP) { 
            while (true) {
                if (G.gameOn() && white == PLAYERTYPE::COMP && G.getTurn() == 'w'){
                    G.getBoard().makeMove(whiteComp.cMove(G.getBoard()));
                    G.display();
                    G.flipTurn();
                    bool inCheck = false;
                    int condition = G.getBoard().isCheckStalemate(G.getTurn(), inCheck);
                    if (inCheck && condition == 0) {
                        std::cout << ((G.getTurn() == 'w') ? "White" : "Black") << " is in check." << std::endl;
                    }
                    scoreUpdate(condition, whiteScore, blackScore, G);
                    if (condition != 0) break;
                }
                if (G.gameOn() && black == PLAYERTYPE::COMP && G.getTurn() == 'b') {
                    G.getBoard().makeMove(blackComp.cMove(G.getBoard()));
                    G.display();
                    G.flipTurn();
                    bool inCheck = false;
                    int condition = G.getBoard().isCheckStalemate(G.getTurn(), inCheck);
                    if (inCheck && condition == 0) {
                        std::cout << ((G.getTurn() == 'w') ? "White" : "Black") << " is in check." << std::endl;
                    }
                    scoreUpdate(condition, whiteScore, blackScore, G);
                    if (condition != 0) break;
                }
            }
            white = PLAYERTYPE::HUMAN; //Reset state
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
