#include "king.h"
#include "info.h"
#include "board.h"
#include "move.h"
extern Move newMove;

King::King(shared_ptr<Cell> location, Colour colour): Piece{location, colour, 1}, checkCastling{true} {}

void King::moveIn(int row, int col) {
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
    if (row - 1 >= 0 && col - 1 >= 0) attach(getLocation()->getBoard()->getCell(row-1, col-1));
    
    if (row - 1 >= 0 && col + 1 < 8) attach(getLocation()->getBoard()->getCell(row-1, col+1));
    
    if (row - 1 >= 0) attach(getLocation()->getBoard()->getCell(row-1, col));

    if (row + 1 < 8 && col - 1 >= 0) attach(getLocation()->getBoard()->getCell(row+1, col-1));
    
    if (row + 1 < 8 && col + 1 < 8) attach(getLocation()->getBoard()->getCell(row+1, col+1));
    
    if (row + 1 < 8) attach(getLocation()->getBoard()->getCell(row+1, col));

    if (col - 1 >= 0) attach(getLocation()->getBoard()->getCell(row, col-1));
    
    if (col + 1 < 8) attach(getLocation()->getBoard()->getCell(row, col+1));

    notifyObserversIn(); 
}
