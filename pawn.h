#include "piece.h"



class Pawn : public Piece {
    bool checkFirstMove;
    vector<shared_ptr<Observer<Info>>> whereCanICapture;
    public:
    Pawn(shared_ptr<Cell> location, Colour colour);
    void pawnMove(int row, int col);
    void moveIn(int row, int col) override;
    void notifyIn(Subject<Info> &whoFrom) override;
    void notifyOut(Subject<Info> &whoFrom) override;
};




