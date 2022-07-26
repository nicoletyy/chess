#include "queen.h"
#include "info.h"
#include "board.h"
#include "move.h"
extern Move newMove;


Queen::Queen(shared_ptr<Cell> location, Colour colour): Piece{location, colour, 2} {}

void Queen::moveIn(int row, int col) {
    if (getLocation()->getBoard()->getCell(row, col)->getPiece() != nullptr &&
	getLocation()->getBoard()->getCell(row, col)->getPiece()->getColour() == getColour()) {
        InvalidMove invalidMove;
        throw(invalidMove);
    }
    changeLocation(row, col);
    setValid(true);
    if (getLocation()->getBoard()->getCell(row, col)->getPiece() != nullptr) {
        getLocation()->getBoard()->getCell(row, col)->getPiece()->setValid(false);
        newMove.capturing = true;
        newMove.captured = getLocation()->getBoard()->getCell(row, col)->getPiece();
    }
    shared_ptr<Piece> p (this);
    getLocation()->getBoard()->getCell(row, col)->setPiece(p);
    detachAll();
    for (int i = row + 1, j = col + 1; i < 8 && j < 8; ++i, ++j) {
        if (getLocation()->getBoard()->getCell(i,j)->getPiece() == nullptr) {
            attach(getLocation()->getBoard()->getCell(i,j));
        }
        else {
            attach(getLocation()->getBoard()->getCell(i,j));
            break;
        }
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j < 8; --i, ++j) {
        if (getLocation()->getBoard()->getCell(i,j)->getPiece() == nullptr) {
            attach(getLocation()->getBoard()->getCell(i,j));
        }
        else {
            attach(getLocation()->getBoard()->getCell(i,j));
            break;
        }
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
        if (getLocation()->getBoard()->getCell(i,j)->getPiece() == nullptr) {
            attach(getLocation()->getBoard()->getCell(i,j));
        }
        else {
            attach(getLocation()->getBoard()->getCell(i,j));
            break;
        }
    }
    for (int i = row + 1, j = col - 1; i < 8 && j >= 0; ++i, --j) {
        if (getLocation()->getBoard()->getCell(i,j)->getPiece() == nullptr) {
            attach(getLocation()->getBoard()->getCell(i,j));
        }
        else {
            attach(getLocation()->getBoard()->getCell(i,j));
            break;
        }
    }
    for (int j = col + 1; j < 8; ++j) {
        if (getLocation()->getBoard()->getCell(row,j)->getPiece() == nullptr) {
            attach(getLocation()->getBoard()->getCell(row,j));
        }
        else {
            attach(getLocation()->getBoard()->getCell(row,j));
            break;
        }
    }
    for (int j = col - 1; j >= 0; --j) {
        if (getLocation()->getBoard()->getCell(row,j)->getPiece() == nullptr) {
            attach(getLocation()->getBoard()->getCell(row,j));
        }
        else {
            attach(getLocation()->getBoard()->getCell(row,j));
            break;
        }
    }
    for (int i = row - 1; i >= 0; --i) {
        if (getLocation()->getBoard()->getCell(i,col)->getPiece() == nullptr) {
            attach(getLocation()->getBoard()->getCell(i,col));
        }
        else {
            attach(getLocation()->getBoard()->getCell(i,col));
            break;
        }
    }
    for (int i = row + 1; i < 8; ++i) {
        if (getLocation()->getBoard()->getCell(i,col)->getPiece() == nullptr) {
            attach(getLocation()->getBoard()->getCell(i,col));
        }
        else {
            attach(getLocation()->getBoard()->getCell(i,col));
            break;
        }
    }

    notifyObserversIn(); 
}






void Queen::notifyIn(Subject<Info> &whoFrom) {
    Info info = whoFrom.getInfo();
    int cRow = info.row;
    int cCol = info.col;
    int pRow = getLocation()->getRow();
    int pCol = getLocation()->getCol();
    if (cRow == pRow && cCol > pCol) {
        for (int i = cCol + 1; i < 8; ++i) {
            detach(getLocation()->getBoard()->getCell(cRow, i));
        }
    }
    if (cRow == pRow && cCol < pCol) {
        for (int i = cCol - 1; i >= 0; --i) {
            detach(getLocation()->getBoard()->getCell(cRow, i));
        }
    }
    if (cRow > pRow && cCol == pCol) {
        for (int i = cRow + 1; i < 8; ++i) {
            detach(getLocation()->getBoard()->getCell(i, cCol));
        }
    }
    if (cRow < pRow && cCol == pCol) {
        for (int i = cRow - 1; i >= 0; --i) {
            detach(getLocation()->getBoard()->getCell(i, cCol));
        }
    }
    if (cRow > pRow && cCol > pCol) {
        for (int i = cRow + 1, j = cCol + 1; i < 8 && j < 8; ++i, ++j) {
            detach(getLocation()->getBoard()->getCell(i,j));
        }
    }
    if (cRow < pRow && cCol > pCol) {
        for (int i = cRow - 1, j = cCol + 1; i >= 0 && j < 8; --i, ++j) {
            detach(getLocation()->getBoard()->getCell(i,j));
        }
    }
    if (cRow > pRow && cCol < pCol) {
        for (int i = cRow + 1, j = cCol - 1; i < 8 && j >= 0; ++i, --j) {
            detach(getLocation()->getBoard()->getCell(i,j));
        }
    }
    if (cRow < pRow && cCol < pCol) {
        for (int i = cRow - 1, j = cCol - 1; i >= 0 && j >= 0; --i, --j) {
            detach(getLocation()->getBoard()->getCell(i,j));
        }
    }
}



void Queen::notifyOut(Subject<Info> &whoFrom) {
    Info info = whoFrom.getInfo();
    int cRow = info.row;
    int cCol = info.col;
    int pRow = getLocation()->getRow();
    int pCol = getLocation()->getCol();
    if (cRow == pRow && cCol > pCol) {
        for (int i = cCol + 1; i < 8; ++i) {
            if (getLocation()->getBoard()->getCell(cRow, i)->getPiece() == nullptr) {
                attach(getLocation()->getBoard()->getCell(cRow, i));
                getLocation()->getBoard()->getCell(cRow, i)->notifyIn(*this);
            }
        }
    }
    if (cRow == pRow && cCol < pCol) {
        for (int i = cCol - 1; i >= 0; --i) {
            if (getLocation()->getBoard()->getCell(cRow, i)->getPiece() == nullptr) {
                attach(getLocation()->getBoard()->getCell(cRow, i));
                getLocation()->getBoard()->getCell(cRow, i)->notifyIn(*this);
            }
        }
    }
    if (cRow > pRow && cCol == pCol) {
        for (int i = cRow + 1; i < 8; ++i) {
            if (getLocation()->getBoard()->getCell(i, cCol)->getPiece() == nullptr) {
                attach(getLocation()->getBoard()->getCell(i, cCol));
                getLocation()->getBoard()->getCell(i, cCol)->notifyIn(*this);
            }
        }
    }
    if (cRow < pRow && cCol == pCol) {
        for (int i = cRow - 1; i >= 0; --i) {
            if (getLocation()->getBoard()->getCell(i, cCol)->getPiece() == nullptr) {
                attach(getLocation()->getBoard()->getCell(i, cCol));
                getLocation()->getBoard()->getCell(i,cCol)->notifyIn(*this);
            }
        }
    }
    if (cRow > pRow && cCol > pCol) {
        for (int i = cRow + 1, j = cCol + 1; i < 8 && j < 8; ++i, ++j) {
            if (getLocation()->getBoard()->getCell(i,j)->getPiece() == nullptr) {
                attach(getLocation()->getBoard()->getCell(i,j));
                getLocation()->getBoard()->getCell(i,j)->notifyIn(*this);
            }
        }
    }
    if (cRow < pRow && cCol > pCol) {
        for (int i = cRow - 1, j = cCol + 1; i >= 0 && j < 8; --i, ++j) {
            if (getLocation()->getBoard()->getCell(i,j)->getPiece() == nullptr) {
                attach(getLocation()->getBoard()->getCell(i,j));
                getLocation()->getBoard()->getCell(i,j)->notifyIn(*this);
            }
        }
    }
    if (cRow > pRow && cCol < pCol) {
        for (int i = cRow + 1, j = cCol - 1; i < 8 && j >= 0; ++i, --j) {
            if (getLocation()->getBoard()->getCell(i,j)->getPiece() == nullptr) {
                attach(getLocation()->getBoard()->getCell(i,j));
                getLocation()->getBoard()->getCell(i,j)->notifyIn(*this);
            }
        }
    }
    if (cRow < pRow && cCol < pCol) {
        for (int i = cRow - 1, j = cCol - 1; i >= 0 && j >= 0; --i, --j) {
            if (getLocation()->getBoard()->getCell(i,j)->getPiece() == nullptr) {
                attach(getLocation()->getBoard()->getCell(i,j));
                getLocation()->getBoard()->getCell(i,j)->notifyIn(*this);
            }
        }
    }
}




