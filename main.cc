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
    while (std::cin >> fCol >> fRow >> tCol >> tRow) { 
        //Make 0 indexing
        fRow--;
        tRow--;
        std::cout << fCol << ' ' << fRow << ' ' << tCol << ' ' << tRow << '\n';
        Position f = {fCol - 'a', 7 - fRow};
        Position t = {tCol - 'a', 7 - tRow};
        std::cout << f.getCol() << '\n';

        Piece* p = B.getPieceAt(f);
        if (p == nullptr) {
            std::cout << "No piece located there." << std::endl;
            break;
        } else { 
            B.makeMove({f, t, p, nullptr, '0'});
        }

        B.display();
    }

    return 0;

}
