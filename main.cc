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

int main () {

    std::cout << "Chess\n";

    Board B;

    B.display();

    std::vector<std::unique_ptr<Piece>>& g = B.getGrid();
    for (auto& p: g) {
        std::cout << p.get()->getPosition().getCol() << ' ';
    } std::cout << '\n';

    B.makeMove(B.getGrid()[16].get()->getLegalMoves()[1]);

    B.display();

    return 0;

}
