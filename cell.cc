#include "cell.h"
#include <memory>
#include <iostream>
using namespace std;

Cell::Cell(int row, int col, Colour colour, Board * b): piece{nullptr}, row{row}, col{col}, colour{colour}, board{b} {} 



int Cell::getRow() {return row;}

int Cell::getCol() {return col;}

shared_ptr<Piece> Cell::getPiece() { return piece; }

void Cell::setPiece(shared_ptr<Piece> p ) {piece = p;}

void Cell::unsetPiece() {
	piece->setValid(false);
	piece = nullptr;
}


Info Cell::getInfo() const {
    return Info{row, col, piece->getIndex(), piece->getValidity(), piece->getColour(), colour};
}


Colour Cell::getColour() {
	return colour;
}


Board *Cell::getBoard() {
	return board;
}


void Cell::notifyIn(Subject<Info> &whoFrom) {
	//cout << "cellNotify" << endl;
	Piece *temp = dynamic_cast<Piece *>(&whoFrom);
	std::shared_ptr<Observer<Info>> p (temp);
	attach(p);
}


void Cell::notifyOut(Subject<Info> &whoFrom) {
    Piece *temp = dynamic_cast<Piece *>(&whoFrom);
    std::shared_ptr<Observer<Info>> p (temp);
    detach(p);
}

bool Cell::hasObserver() {
	for (int i = 0; i < (int) getObserver().size(); ++i) {
		Piece *temp = dynamic_cast<Piece *>(getObserver()[i].get());
                if (temp->getColour() != piece->getColour()) return true;
        }
        return false;
} 


bool Cell::underAttack() {
    if (piece != nullptr) {
        return hasObserver();
    }
    return false;
}



