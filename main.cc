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

// Read in player given cmd s
// returns -1 for failed read
// 0 = human
// 1, 2, 3, 4 for computer level
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
        //Read level
        iss >> level;
        if (firstPart == "computer" && 1 <= level && level <= 4){
            player = PLAYERTYPE::COMP;
            compPlayer = ComputerPlayer (level, colour);
            return level;
        }
        return FAIL;
    }
} 

void scoreUpdate(int condition, double& whiteScore, double& blackScore, Game& G) {
    if (condition) {
        if (condition == 2) {
            if (G.getTurn() == 'w') {
                std::cout << "Checkmate! Black wins!" << std::endl;
                ++blackScore;
            } else {
                std::cout << "Checkmate! White wins!" << std::endl;
                ++whiteScore;
            }
        } else if (condition == 1) {
            std::cout << "Stalemate!" << std::endl;
            blackScore += 0.5;
            whiteScore += 0.5;
        }
        G.display();
    }
}

int main (int argc, char** argv) {

    std::cout << "Welcome to Chess :D" << std::endl;

    double whiteScore = 0, blackScore = 0;
    PLAYERTYPE white = PLAYERTYPE::HUMAN;
    PLAYERTYPE black = PLAYERTYPE::HUMAN;
    ComputerPlayer whiteComp (1, 'w'), blackComp (1, 'b');

    // Wrap in outer loop to reinstantiate Game after it completes
    while (true) {

        Game G; 

        char fCol, tCol;
        int fRow, tRow;

        // Read whole line
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

            //EOF
            if (!std::getline(std::cin, line)) break;
            std::istringstream iss {line};

            //Read the first word of the line, the command
            std::string cmd;
            iss >> cmd;
            if (cmd == "game") {
                if (!G.gameOn()){
                    std::string player1 = "", player2 = "";
                    iss >> player1 >> player2;
                    if (readPlayer(player1, white, whiteComp, 'w') == FAIL) std::cout << "Invalid white player" << std::endl;
                    else if (readPlayer(player2, black, blackComp, 'b') == FAIL) std::cout << "Invalid black player" << std::endl;
                    else G.startGame();
                }
                else std::cout << "A game is active, please resign or finish!" << std::endl;
            }
            else if (cmd == "move"){
                if (G.gameOn()){
                    iss >> fCol >> fRow >> tCol >> tRow;
                    //For pawn promotion
                    char promo = '0';
                    iss >> promo;
                    G.makeMove(fCol, fRow, tCol, tRow, promo);
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
                if (G.gameOn()){
                    if (G.getTurn() == 'w') {
                        std::cout << "Black wins!" << std::endl;
                        ++blackScore;
                    } else {
                        std::cout << "White wins!" << std::endl;
                        ++whiteScore;
                    }
                    break;
                }
                else std::cout << "No active game. Please start a game using \"game <whiteplayer> <blackplayer>\"" << std::endl;
            }
            else if (cmd == "history" && argc > 1 && std::string(argv[1]) == "-enhancement") {
                if (G.gameOn()){
                    std::stack<Move> temp;
                    auto copy = G.getBoard().getHistory();
                    // Reverse the stack
                    while (!copy.empty()) {
                        temp.push(copy.top());
                        copy.pop();
                    }
                    // Print in correct order
                    while (!temp.empty()) {
                        std::cout << temp.top() << std::endl;
                        temp.pop();
                    }
                }
                else std::cout << "No active game. Please start a game using \"game <whiteplayer> <blackplayer>\"" << std::endl;
            }
            else{
                //Invalid commands
                std::cout << "Unrecognized command: " << cmd << std::endl;
            }

            G.display();

        }

        // Two computer players fight
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
            //Reset state
            white = PLAYERTYPE::HUMAN;
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
