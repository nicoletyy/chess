#ifndef _MOVE_H_
#define _MOVE_H_
#include <memory>

class Piece;

struct Move {
	std::shared_ptr<Piece> lastMovedPiece;
        int start_r, start_c, end_r, end_c;
        bool capturing;
	std::shared_ptr<Piece> captured;
        Move(std::shared_ptr<Piece>, int, int, int, int, bool, std::shared_ptr<Piece>);
};

#endif
