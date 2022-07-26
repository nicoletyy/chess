#include "player.h"
#include "board.h"


Player::Player(Colour c, float grade) : colour{c}, grade{grade} {} 


void Player::move() {};

void Player::updateGrade(float g) {
        grade += g;
}

void Player::set(std::shared_ptr<Piece> p) {
	pieces.push_back(p);
}

void Player::exitSetup() {
	vector<std::shared_ptr<Piece>> newPieces;
	for (int i = 0; i < (int)pieces.size(); i++) {
		if(pieces[i]->getValidity() == 1) {
			newPieces.push_back(pieces[i]);
		}
	}
	pieces = newPieces;
}

void Player::clearPieces() {
        pieces.clear();
}

bool Player::checkStalement() {
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
                } catch(InvalidMove inMove) {
                        pieces[i]->moveIn(row, col);
                        continue;
                }
		pieces[i]->moveIn(row, col);
                // check if the i-th piece has places to move into
                if(pieces[i]->getObserver().size() > 2) return false;
	}
	return true;
}

float Player::getScore(){
        return grade;
}
