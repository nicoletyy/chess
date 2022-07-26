#include "computer1.h"
#include "board.h"
#include "move.h"
extern Move newMove;

ComputerLevel1::ComputerLevel1(Colour colour): Player{colour, 0} {}

void ComputerLevel1::move(int start_r, int start_c, int end_r, int end_c) {
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

void ComputerLevel1::move() {
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
        if(pieces[i]->getObserver().size() > 2) {
		for(int j = 2; j < (int)pieces[i]->getObserver().size(); j++) {
			try {
				shared_ptr<Cell> tmp = dynamic_pointer_cast<Cell>(pieces[i]->getObserver()[j]);
				pieces[i]->moveIn(tmp->getRow(), tmp->getCol());
				newMove.start_r = row;
				newMove.start_c = col;
				newMove.end_r = tmp->getRow();
				newMove.end_c = tmp->getCol();
				return;
			} catch(InvalidMove in) {
				pieces[i]->moveOut();
			}
		}
	}
	pieces[i]->moveIn(row, col);
	}
}

