#include "computer2.h"
#include "move.h"
#include "board.h"
extern Move newMove;

ComputerLevel2::ComputerLevel2(Colour colour): Player{colour, 0} {}

void ComputerLevel2::move(int start_r, int start_c, int end_r, int end_c) {
        for(int i = 0; i < (int)pieces.size(); i++) {
                if((pieces[i]->getInfo().row == start_r) &&
                                (pieces[i]->getInfo().col == start_c)) {
                        pieces[i]->moveOut();
                        pieces[i]->moveIn(end_r, end_c);
                        newMove.start_r = start_r;
			newMove.start_c = start_c;
			newMove.end_r = end_r;
			newMove.end_c = end_c;
                        return;
                }
        }
}


// Give each possible move a score. 
// Initial score is one, and: 
// If it is a capturing move, score is two;
// If the move checks, it takes priority. 
void ComputerLevel2::move() {
	// record the score of the best choice so far
	int bestChoice = 0;
	// record the infomation of the best choice so far
	int start_r, start_c, end_r, end_c;
	// Loop through all possible moves to find the highest-scored move
	for(int i = 0; i < (int)pieces.size(); i++) {
		// check if the i-th piece is in the board
		if(pieces[i]->getValidity() == 0) continue;
		// get the row and column of the i-th piece
		int row = pieces[i]->getInfo().row;
		int col = pieces[i]->getInfo().col;
		// check if the i-th piece can leave its original position
                // If the answer is NO, break and try the next piece
                try {
                        pieces[i]->moveOut();
                } catch(InvalidMove) {
                        pieces[i]->moveIn(row, col);
                        continue;
                }
                // check if the i-th piece has places to move into
                // grade for all possible moves and update the bestChoice info
		for(int j = 2; j < (int)pieces[i]->getObserver().size(); j++) {
                        int score = 0;
			shared_ptr<Cell> tmp = dynamic_pointer_cast<Cell>(pieces[i]->getObserver()[j]);
                        if(tmp->getPiece() == nullptr) {
                                score = 1;
                        } else if(tmp->getPiece()->getColour() ==
                                  pieces[i]->getColour()) {
                                continue;
                        } else if(tmp->getPiece()->getIndex() == 1) {
                                pieces[i]->moveIn(tmp->getRow(), tmp->getCol());
                                newMove.start_r = row;
				newMove.start_c = col;
				newMove.end_r = tmp->getRow();
				newMove.end_c = tmp->getCol();
                                return;
                        } else {
                                score = 2;
                        }
                        if(score > bestChoice) {
                                bestChoice = score;
                                start_r = row;
                                start_c = col;
                                end_r = tmp->getRow();
                                end_c = tmp->getCol();
                        }
                }	
		pieces[i]->moveIn(row, col);
	}
        move(start_r, start_c, end_r, end_c);
}

