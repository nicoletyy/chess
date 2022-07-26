#include "move.h"
#include <iostream>
using namespace std;


Move::Move(std::shared_ptr<Piece> lastMovedPiece, int start_r, int start_c, 
            int end_r, int end_c, bool capturing, std::shared_ptr<Piece> captured):
    lastMovedPiece{lastMovedPiece}, start_r{start_r}, start_c{start_c}, 
    end_r{end_r}, end_c{end_c}, capturing{capturing}, captured{captured} {}
