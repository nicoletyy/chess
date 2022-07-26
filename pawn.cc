#include "pawn.h"
#include "info.h"
#include "board.h"
#include "move.h"

extern Move newMove;
extern bool promotion;

Pawn::Pawn(shared_ptr<Cell> location, Colour colour): Piece{location, colour, 6}, checkFirstMove{true} {}


void Pawn::moveIn(int row, int col) {
    Colour pColour = getColour();
    if (getLocation()->getBoard()->getCell(row, col)->getPiece() != nullptr &&
        getLocation()->getBoard()->getCell(row, col)->getPiece()->getColour() == getColour()) {
	InvalidMove invalidMove;
        throw(invalidMove);
    }
    int pRow = getLocation()->getRow();
    int pCol = getLocation()->getCol();
    if (pColour == Colour::White && row == pRow - 1 && (col == pCol + 1 || col == pCol - 1) &&
        getLocation()->getBoard()->getCell(row, col)->getPiece() != nullptr) {
            getLocation()->getBoard()->getCell(row, col)->getPiece()->setValid(false);
    }

    else if (pColour == Colour::Black && row == pRow + 1 && (col == pCol + 1 || col == pCol - 1) &&
        getLocation()->getBoard()->getCell(row, col)->getPiece() != nullptr) {
            getLocation()->getBoard()->getCell(row, col)->getPiece()->setValid(false);
            newMove.capturing = true;
            newMove.captured = getLocation()->getBoard()->getCell(row, col)->getPiece();
    }
    changeLocation(row, col);
    setValid(true);
    shared_ptr<Piece> p (this);
    getLocation()->getBoard()->getCell(row, col)->setPiece(p);
    detachAll();

    if (pColour == Colour::White) {
        if (row - 1 >= 0 && getLocation()->getBoard()->getCell(row-1, col)->getPiece() == nullptr) attach(getLocation()->getBoard()->getCell(row-1, col));
        else return;
        if (checkFirstMove) {
            if (row - 2 >= 0 && getLocation()->getBoard()->getCell(row-2, col)->getPiece() == nullptr) {
                attach(getLocation()->getBoard()->getCell(row-2, col));
            }
        }
    }
    if (pColour == Colour::Black) {
        if (row + 1 < 8 && getLocation()->getBoard()->getCell(row+1, col)->getPiece() == nullptr) attach(getLocation()->getBoard()->getCell(row+1, col));
        else return;
        if (checkFirstMove) {
            if (row + 2 < 8 && getLocation()->getBoard()->getCell(row+2, col)->getPiece() == nullptr) {
                attach(getLocation()->getBoard()->getCell(row+2, col));
            }
        }
    }

    notifyObserversIn();
    whereCanICapture.clear();
    if (pColour == Colour::White) {
        if (row-1 >= 0 && col+1 < 8) whereCanICapture.emplace_back(getLocation()->getBoard()->getCell(row-1, col+1));
        if (row-1 >= 0 && col-1 >= 0) whereCanICapture.emplace_back(getLocation()->getBoard()->getCell(row-1, col-1));
        if (row-1 >= 0 && col-1 >= 0) getLocation()->getBoard()->getCell(row-1, col-1)->notifyIn(*this);
        if (row-1 >= 0 && col+1 < 8) getLocation()->getBoard()->getCell(row-1, col+1)->notifyIn(*this);
	
    }
    else if (pColour == Colour::Black) {
	  
        if (row + 1 < 8 && col+1 < 8) whereCanICapture.emplace_back(getLocation()->getBoard()->getCell(row+1, col+1));
        if (row+1 < 8 && col - 1 >= 0) whereCanICapture.emplace_back(getLocation()->getBoard()->getCell(row+1, col-1));
        if (row + 1 < 8 && col+1 < 8) getLocation()->getBoard()->getCell(row+1, col+1)->notifyIn(*this);
        if (row+1 < 8 && col - 1 >= 0) getLocation()->getBoard()->getCell(row+1, col-1)->notifyIn(*this);
    }
}


void Pawn::pawnMove(int row, int col) {
    Colour pColour = getColour();
    int pRow = getLocation()->getRow();
    int pCol = getLocation()->getCol();
    if (row >= 8 || row < 0 || col >= 8 || col < 0) {
        InvalidMove invalidMove;
        throw(invalidMove);
    }
    if  (!((pColour == Colour::White && row == pRow - 1 && (col == pCol + 1 || col == pCol - 1) &&
        getLocation()->getBoard()->getCell(row, col)->getPiece() != nullptr) ||
         (pColour == Colour::Black && row == pRow + 1 && (col == pCol + 1 || col == pCol - 1) &&
        getLocation()->getBoard()->getCell(row, col)->getPiece() != nullptr) ||
        (pColour == Colour::White &&
        ((row == pRow - 1 && col == pCol && getLocation()->getBoard()->getCell(row, col)->getPiece() == nullptr) ||
        (row == pRow - 2 && col == pCol && 
        getLocation()->getBoard()->getCell(row+1, col)->getPiece() == nullptr &&
        getLocation()->getBoard()->getCell(row, col)->getPiece() == nullptr && checkFirstMove))) ||
        (pColour == Colour::Black &&
        ((row == pRow + 1 && col == pCol && getLocation()->getBoard()->getCell(row, col)->getPiece() == nullptr) ||
        (row == pRow + 2 && col == pCol && 
        getLocation()->getBoard()->getCell(row+1, col)->getPiece() == nullptr &&
        getLocation()->getBoard()->getCell(row, col)->getPiece() == nullptr && checkFirstMove))))) {
            InvalidMove invalidMove;
            throw(invalidMove);
    }
        
    try {
        moveOut();
    }
    catch (InvalidMove invalidMove) {
        moveIn(pRow, pCol);
        InvalidMove in;
        throw(in);
    }


    try {
        moveIn(row, col);
    }
    catch (InvalidMove invalidMove) {
        InvalidMove in;
        throw(in);
    }

    if (checkFirstMove) checkFirstMove = false;
    shared_ptr<Piece> p (this);
    newMove.lastMovedPiece = p;
    if (pColour == Colour::White && getLocation()->getRow() == 0) {
        promotion = true;
    }
    if (pColour == Colour::Black && getLocation()->getRow() == 7) {
        promotion = true;
    }


}



void Pawn::notifyIn(Subject<Info> &whoFrom) {
    Colour pColour = getColour();
    Info info = whoFrom.getInfo();
    int cRow = info.row;
    int cCol = info.col;
    int pRow = getLocation()->getRow();
    int pCol = getLocation()->getCol();
    if (pColour == Colour::White) {
        if (cRow == pRow - 1 && cCol == pCol) {
            Cell * p = dynamic_cast<Cell *>(&whoFrom);
            shared_ptr<Cell> spc (p);
            detach(spc);
            if (cRow-1 >= 0) detach(getLocation()->getBoard()->getCell(cRow-1, cCol));
        }
        if (cRow == pRow - 2 && cCol == pCol) {
            Cell * p = dynamic_cast<Cell *>(&whoFrom);
            shared_ptr<Cell> spc (p);
            detach(spc);
        }
    }
    if (pColour == Colour::Black) {
        if (cRow == pRow + 1 && cCol == pCol) {
	    Cell * p = dynamic_cast<Cell *>(&whoFrom);
	    shared_ptr<Cell> spc (p);
            detach(spc);
            if (cRow+1 < 8) detach(getLocation()->getBoard()->getCell(cRow+1, cCol));
        }
        if (cRow == pRow + 2 && cCol == pCol) {
            Cell * p = dynamic_cast<Cell *>(&whoFrom);
            shared_ptr<Cell> spc (p);
            detach(spc);
        }
    }

} 


void Pawn::notifyOut(Subject<Info> &whoFrom) {
    Colour pColour = getColour();
    Info info = whoFrom.getInfo();
    int cRow = info.row;
    int cCol = info.col;
    int pRow = getLocation()->getRow();
    int pCol = getLocation()->getCol();

    if (pColour == Colour::White) {
        if (cRow == pRow - 1 && cCol == pCol) {
            Cell * p = dynamic_cast<Cell *>(&whoFrom);
            shared_ptr<Cell> spc (p);
            attach(spc);
            p->notifyIn(*this);
            if (cRow - 1 >= 0 &&
                checkFirstMove && getLocation()->getBoard()->getCell(cRow-1, cCol)->getPiece() == nullptr) {
                attach(getLocation()->getBoard()->getCell(cRow-1, cCol));
            }
        }
        else if (cRow == pRow - 2 && cCol == pCol && checkFirstMove) {
            Cell * p = dynamic_cast<Cell *>(&whoFrom);
            shared_ptr<Cell> spc (p);
            attach(spc);
        }
    }
    if (pColour == Colour::Black) {
        if (cRow == pRow + 1 && cCol == pCol) {
            Cell * p = dynamic_cast<Cell *>(&whoFrom);
            shared_ptr<Cell> spc (p);
            attach(spc);
            p->notifyIn(*this);
            if (cRow + 1 < 8 &&
                checkFirstMove && getLocation()->getBoard()->getCell(cRow+1, cCol)->getPiece() == nullptr) {
                attach(getLocation()->getBoard()->getCell(cRow+1, cCol));
            }
        }
        else if (cRow == pRow + 2 && cCol == pCol && checkFirstMove) {
            Cell * p = dynamic_cast<Cell *>(&whoFrom);
            shared_ptr<Cell> spc (p);
            attach(spc);
        }
    }


}




