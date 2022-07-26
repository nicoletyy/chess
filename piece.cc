#include "piece.h"
#include "board.h"
#include "move.h"

#include <iostream>
using namespace std;

extern Move newMove;

Piece::Piece(shared_ptr<Cell> location, Colour colour, int index): location{location}, colour{colour}, index{index}, valid{false} {}



Colour Piece::getColour() {return colour;}

int Piece::getIndex() {return index;}

Info Piece::getInfo() const{
    return Info{location->getRow(), location->getCol(), index, valid, colour, location->getColour()};
}

bool Piece::getValidity() {return valid;}


shared_ptr<Cell> Piece::getLocation() {
    return location;
}

void Piece::changeLocation(int row, int col) {
    location = location->getBoard()->getCell(row, col);
}

void Piece::setValid(bool validity) {
    valid = validity;
}




void Piece::moveOut() {
    notifyObserversOut();
  
    setValid(false);
   
    shared_ptr<Piece> p (nullptr);
    location->setPiece(p);
   
    if (colour == Colour::White) {
        if (location->getBoard()->getWhiteKing()->hasObserver()) {
          
		InvalidMove invalidMove;
            throw(invalidMove);
        }
    }
    if (colour == Colour::Black) {
        if (location->getBoard()->getBlackKing()->hasObserver()) {
           
		InvalidMove invalidMove;
            throw(invalidMove);
        }
    }
}


void Piece::move(int row, int col) {
    int original_row = getLocation()->getRow();
    int original_col = getLocation()->getCol();
    if (row >= 8 || row < 0 || col >= 8 || col < 0) {
        InvalidMove invalidMove;
        throw(invalidMove);
    }
    
    try {
        moveOut();
    }
    catch (InvalidMove invalidMove) {
        moveIn(original_row, original_col);
        InvalidMove i;
        throw(i);
    }
    try {
        moveIn(row, col);
    }
    catch (InvalidMove invalidMove) {
        InvalidMove i;
        throw(i);
    }
    shared_ptr<Piece> sp (this);
    newMove.lastMovedPiece = sp;

    if (location->getBoard()->getCell(original_row+1, original_col)->getPiece()->getIndex() == 6 &&
        location->getBoard()->getCell(original_row+1, original_col)->getPiece()->getColour() == Colour::White) {
            location->getBoard()->getCell(original_row+1, original_col)->getPiece()->notifyOut(*this);
    }
    if (location->getBoard()->getCell(original_row+2, original_col)->getPiece()->getIndex() == 6 &&
        location->getBoard()->getCell(original_row+2, original_col)->getPiece()->getColour() == Colour::White &&
        location->getBoard()->getCell(original_row+1, original_col)->getPiece() == nullptr) {
            location->getBoard()->getCell(original_row+2, original_col)->getPiece()->notifyOut(*this);
    }

    if (location->getBoard()->getCell(original_row-1, original_col)->getPiece()->getIndex() == 6 &&
        location->getBoard()->getCell(original_row-1, original_col)->getPiece()->getColour() == Colour::Black) {
            location->getBoard()->getCell(original_row-1,original_col)->getPiece()->notifyOut(*this);
    }
    if (location->getBoard()->getCell(original_row-2, original_col)->getPiece()->getIndex() == 6 &&
        location->getBoard()->getCell(original_row-2, original_col)->getPiece()->getColour() == Colour::Black &&
        location->getBoard()->getCell(original_row-1, original_col)->getPiece() == nullptr) {
            location->getBoard()->getCell(original_row-2, original_col)->getPiece()->notifyOut(*this);
    }

}



bool Piece::hasObserver() {return true;} 

bool Piece::underAttack() {
	return location->underAttack();
}








