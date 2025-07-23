#include "ComputerPlayer.h" 

ComputerPlayer::ComputerPlayer(int l, char c) : level{l}, colour{c} {};

Move ComputerPlayer::lv1Move(Board* b) { // finds first piece of same colour in grid, returns first legal move
    for (size_t i = 0; i < b->getGrid().size(); ++i) { 
        if (b->getGrid()[i].get()->getColour() == colour) { 
            Piece* p = b->getGrid()[i].get();
            return p->getLegalMoves()[0];
        }
    }
}

Move ComputerPlayer::lv2Move(Board* b) { 
    for (size_t i = 0; i < b->getGrid().size(); ++i) { 
        if (b->getGrid()[i].get()->getColour() == colour) { 
            Piece* p = b->getGrid()[i].get();
            for (auto &move : p->getLegalMoves()) { 
                if (move.getCap()) return move; // returns a capturing move if possible
                
            }
        }
    }

    return lv1Move(b); // else returns lv1Move

}

Move ComputerPlayer::lv3Move(Board* b) { 
    
}

Move ComputerPlayer::lv4Move(Board* b) { 
    
}