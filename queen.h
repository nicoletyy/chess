#include "piece.h"



class Queen : public Piece {
    public:
    Queen(shared_ptr<Cell> location, Colour colour);
    void moveIn(int row, int col) override;
    void notifyIn(Subject<Info> &whoFrom) override;
    void notifyOut(Subject<Info> &whoFrom) override;
};
