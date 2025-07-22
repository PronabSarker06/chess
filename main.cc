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
#include <algorithm>

int main () {

    std::cout << "Chess\n";

    Board B;
    B.display();
    char fCol, tCol;
    int fRow, tRow;
    char whose_turn = 'w';
    while (std::cin >> fCol >> fRow >> tCol >> tRow) { 
        //Make 0 indexing
        fRow--;
        tRow--;
        //std::cout << fCol << ' ' << fRow << ' ' << tCol << ' ' << tRow << '\n';
        Position f = {fCol - 'a', 7 - fRow};
        Position t = {tCol - 'a', 7 - tRow};

        Piece* p = B.getPieceAt(f);
        if (p == nullptr) {
            std::cout << "No piece located there." << std::endl;
        } else if (p->getColour() != whose_turn) {
            std::cout << "Cannot move your enemy's pieces." << std::endl;
        } else if (B.makeMove({f, t, p, B.getPieceAt(t), '0'})){
            if (whose_turn == 'w') {
                whose_turn = 'b';
            } else {
                whose_turn = 'w';
            }
        }

        B.display();
    }

    return 0;

}
