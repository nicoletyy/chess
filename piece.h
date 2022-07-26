#ifndef _PIECE_H_
#define _PIECE_H_
#include "cell.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "info.h"
#include "subject.h"
#include "observer.h"

class Piece : public Subject<Info>, public Observer<Info> {
    shared_ptr<Cell> location;
    Colour colour;
    int index;
    bool valid;
    
    public:
    Piece(shared_ptr<Cell> location, Colour colour, int index);
    Colour getColour();
    int getIndex();
    Info getInfo() const override;
    bool getValidity();
    shared_ptr<Cell> getLocation();
    void changeLocation(int row, int col);
    void setValid(bool validity);
    virtual void moveIn(int row, int col)=0;
    void moveOut();
    void move(int row, int col);  
    bool hasObserver() override;
    bool underAttack();
};


#endif

