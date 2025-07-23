#include "ComputerPlayer.h" 

ComputerPlayer::ComputerPlayer(int l, char c) : level{l}, colour{c} {};

Move ComputerPlayer::Move(Board* b) { 
    switch (level) { 
        case 1: lv1Move(b, colour);
        case 2: lv2Move(b, colour);
        case 3: lv3Move(b, colour);
        case 4: lv4Move(b, colour);
    }
}

Move lv1Move(Board* b, char colour) { // finds first piece of same colour in grid, returns first legal move
    for (size_t i = 0; i < b->getGrid().size(); ++i) { 
        if (b->getGrid()[i].get()->getColour() == colour) { 
            Piece* p = b->getGrid()[i].get();
            return p->getLegalMoves()[0];
        }
    }
}

Move lv2Move(Board* b, char colour) { 
    for (size_t i = 0; i < b->getGrid().size(); ++i) { 
        if (b->getGrid()[i].get()->getColour() == colour) { 
            Piece* p = b->getGrid()[i].get();
            for (auto &move : p->getLegalMoves()) { 
                if (move.getCap()) return move; // returns a capturing move if possible
                
            }
        }
    }

    return lv1Move(b, colour); // else returns lv1Move

}

Move lv3Move(Board* b, char colour) { 
    
}

Move lv4Move(Board* b, char colour) { 
    
}