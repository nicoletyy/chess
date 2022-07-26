#ifndef __INFO_H__
#define __INFO_H__
#include <cstddef>

enum class Colour { NoColour, Black, White };

struct Info {
  int row, col;
  int pieceType;
  bool valid;
  Colour pieceColour;
  Colour cellColour;
};

#endif


