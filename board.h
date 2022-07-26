#ifndef _BOARD_H_
#define _BOARD_H_
#include "cell.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include <string>
#include <memory>
#include "piece.h"

class Cell;
class Piece;
class TextDisplay;
template <typename InfoType> class Observer;
class InvalidMove{};

class Board {
    std::vector<std::vector<std::shared_ptr<Cell>>> board;
    std::shared_ptr<TextDisplay> td = nullptr;
    std::shared_ptr<Observer<Info>> ob = nullptr;
    bool enPassant = false;
    bool whiteCheck = false;
    bool blackCheck = false;
    bool whiteCheckmate = false;
    bool blackCheckmate = false;
    std::shared_ptr<Piece> blackKing = nullptr;
    std::shared_ptr<Piece> whiteKing = nullptr;

 public:
    Board();
    std::shared_ptr<TextDisplay> getTD() const;
    std::shared_ptr<Observer<Info>> getGD() const;
    void unset(int row, int col);
    void validate();
    shared_ptr<Cell> getCell(int row, int col);
    void setObserver(std::shared_ptr<Observer<Info>> ob);
    bool getWhiteCheckmate() const;
    bool getBlackCheckmate() const;
    bool getWhiteCheck() const;
    bool getBlackCheck() const;
    std::shared_ptr<Piece> getBlackKing();
    std::shared_ptr<Piece> getWhiteKing();
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif

