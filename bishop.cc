#include "bishop.h"
#include "board.h"
#include "info.h"
#include "move.h"
extern Move newMove;

Bishop::Bishop(shared_ptr<Cell> location, Colour colour): Piece{location, colour, 3} {}

void Bishop::moveIn(int row, int col) {
    if (getLocation()->getBoard()->getCell(row, col)->getPiece() != nullptr &&
        getLocation()->getBoard()->getCell(row, col)->getPiece()->getColour() == getColour()) {
        throw InvalidMove();
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

    notifyObserversIn();    
}







void Bishop::notifyIn(Subject<Info> &whoFrom) {
    Info info = whoFrom.getInfo();
    int cRow = info.row;
    int cCol = info.col;
    int pRow = getLocation()->getRow();
    int pCol = getLocation()->getCol();
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
void Bishop::notifyOut(Subject<Info> &whoFrom) {
    Info info = whoFrom.getInfo();
    int cRow = info.row;
    int cCol = info.col;
    int pRow = getLocation()->getRow();
    int pCol = getLocation()->getCol();
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







