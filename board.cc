#include <iostream>
#include <string>
#include "board.h"
#include <vector>

using namespace std;

void Board::setObserver(shared_ptr<Observer<Info>> obs) {
	ob = obs;
}

Board::Board() {
    if (board.size() > 0) {
        board.clear();
        enPassant = false;
        whiteCheck = false;
        blackCheck = false;
        whiteCheckmate = false;
        blackCheckmate = false;
    }
    td = make_shared<TextDisplay>();
    ob = make_shared<GraphicsDisplay>();
    setObserver(ob);

    for (int i = 0; i < 8; i++) {
        vector<shared_ptr<Cell>> v;
        for (int j = 0; j < 8; j++) {
	    if ((i + j) % 2 == 0) {
                shared_ptr<Cell> c = make_shared<Cell>(i, j, Colour::Black, this);
		c->attach(td);
		v.emplace_back(c);
	    } else {
		shared_ptr<Cell> c = make_shared<Cell>(i, j, Colour::White, this);
                c->attach(td);
            	v.emplace_back(c);
	    }
        }
        board.emplace_back(v);
    }
    for (int m = 0; m < 8; m++) {
        for (int n = 0; n < 8; n++) {
            board[m][n]->attach(ob); 
        }
    }
}


void Board::unset(int row, int col) {
    if (board[row][col]->getPiece()) {
        board[row][col]->getPiece()->moveOut();
    }
}

void Board::validate() {
    int whiteKingCount = 0;
    int blackKingCount = 0;
    int whiteKingR, whiteKingC;
    int blackKingR, blackKingC;

    // check pawn
    for (int i = 0; i < 8; i++) {
        Info i1 = board[0][i]->getPiece()->getInfo();
        Info i2 = board[7][i]->getPiece()->getInfo();
        if ((i1.pieceType == 6) || (i2.pieceType == 6)) {
            throw "Invalid setup. Should not set pawns on the first or last row.";
        }
    }
    // check king
    for (int m = 0; m < 8; m++) {
        for (int n = 0; n < 8; n++) {
            Info info = board[m][n]->getPiece()->getInfo();
            if (info.pieceType == 1) {
                if (whiteCheck == true || blackCheck == true) {
                    throw "Invalid setup. Should not be in check.";
                }
                if (info.pieceColour == Colour::Black) {
                    blackKingCount++;
                    blackKingR = m;
                    blackKingC = n;
                }
                if (info.pieceColour == Colour::White) {
                    whiteKingCount++;
                    whiteKingR = m;
                    whiteKingC = n;
                }
            }
        }
        if (whiteKingCount != 1) {
            throw "Invalid setup. You can set only one King.";
        }
        if (blackKingCount != 1) {
            throw "Invalid setup. You can set only one King.";
        }
        blackKing = board[blackKingR][blackKingC]->getPiece();
        whiteKing = board[whiteKingR][whiteKingC]->getPiece();

    }
}

shared_ptr<Cell> Board::getCell(int row, int col) {
    return board[row][col];
}

shared_ptr<TextDisplay> Board::getTD() const { return td; }

shared_ptr<Observer<Info>> Board::getGD() const { return ob; }

bool Board::getWhiteCheckmate() const { return whiteCheckmate; }

bool Board::getBlackCheckmate() const { return blackCheckmate; }

bool Board::getWhiteCheck() const { return whiteCheck; }

bool Board::getBlackCheck() const { return blackCheck; }

ostream & operator<<(ostream &out, const Board &b) {
	out << *(b.td);
	return out;
}



shared_ptr<Piece> Board::getBlackKing() {return blackKing;}

shared_ptr<Piece> Board::getWhiteKing() {return whiteKing;} 


