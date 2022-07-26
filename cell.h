#ifndef _CELL_H_
#define _CELL_H_
#include "subject.h"
#include "observer.h"
#include "info.h"
#include "piece.h"
//#include "textdisplay.h"
//#include "graphicsdisplay.h"
//#include <memory>
using namespace std;

class Board;
class Piece;

class Cell : public Subject<Info>, public Observer<Info> {
    shared_ptr<Piece> piece;
    int row;
    int col;
    Colour colour;
    Board *board;
    public:
    Cell(int, int, Colour, Board *);
    void notifyIn(Subject<Info> &whoFrom);
    void notifyOut(Subject<Info> &whoFrom);
    int getRow();
    int getCol();
    Colour getColour();
    Board *getBoard();
    bool hasObserver() override;
    bool underAttack();
    shared_ptr<Piece> getPiece();
    Info getInfo() const override;
    void unsetPiece();
    void setPiece(shared_ptr<Piece>); 
};

#endif

