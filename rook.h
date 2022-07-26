#include "piece.h"



class Rook : public Piece {
    bool checkCastling;
    public:
    Rook(shared_ptr<Cell> location, Colour colou);
    void moveIn(int row, int col) override;
    void notifyIn(Subject<Info> &whoFrom) override;
    void notifyOut(Subject<Info> &whoFrom) override;

};



