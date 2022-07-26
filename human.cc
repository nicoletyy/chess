#include "human.h"
#include "board.h"


Human::Human(Colour colour): Player{colour, 0} {}

void Human::move(int start_r, int start_c, int end_r, int end_c) {
	for(int i = 0; i < (int) pieces.size(); i++) {
		if((pieces[i]->getInfo().row == start_r) &&
				(pieces[i]->getInfo().col == start_c)) {
			pieces[i]->move(end_r, end_c);
			return;
		}
	}
	InvalidMove in;
	throw (in);
}

