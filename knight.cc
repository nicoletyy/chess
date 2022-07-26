#include "knight.h"
#include "info.h"
#include "board.h"
#include "move.h"
extern Move newMove;


Knight::Knight(shared_ptr<Cell> location, Colour colour): Piece{location, colour, 5} {}

void Knight::moveIn(int row, int col) {
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

    if (row - 2 >= 0 && col - 1 >= 0) attach(getLocation()->getBoard()->getCell(row-2, col-1));
    if (row - 1 >= 0 && col - 2 >= 0) attach(getLocation()->getBoard()->getCell(row-1, col-2));
    
    if (row + 2 < 8 && col + 1 < 8) attach(getLocation()->getBoard()->getCell(row+2, col+1));
    if (row + 1 < 8 && col + 2 < 8) attach(getLocation()->getBoard()->getCell(row+1, col+2));
    
    if (row - 2 >= 0 && col + 1 < 8) attach(getLocation()->getBoard()->getCell(row-2, col+1));
    
    if (row + 2 < 8 && col - 1 >= 0) attach(getLocation()->getBoard()->getCell(row+2, col-1));
    
    
    
    if (row + 1 < 8 && col - 2 >= 0) attach(getLocation()->getBoard()->getCell(row+1, col-2));
    
    if (row - 1 >= 0 && col + 2 < 8) attach(getLocation()->getBoard()->getCell(row-1, col+2));

    notifyObserversIn(); 

}




