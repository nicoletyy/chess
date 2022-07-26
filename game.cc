#include "game.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include "rook.h"
#include "human.h"
#include "computer1.h"
#include "computer2.h"
#include "computer3.h"
#include <memory>

#include <iostream>
using namespace std;

extern Move newMove;

Game::Game(string white, string black) : board{}, previousMoves{} {
    if(white == "human") {
        whitePlayer = make_unique<Human>(Colour::White);
    } else if(white == "computer[1]") {
        whitePlayer = make_unique<ComputerLevel1>(Colour::White);
    } else if(white == "computer[2]") {
        whitePlayer = make_unique<ComputerLevel2>(Colour::White);
    } else {
        whitePlayer = make_unique<ComputerLevel3>(Colour::White);
    }
    if(black == "human") {
        blackPlayer = make_unique<Human>(Colour::Black);
    } else if(black == "computer[1]") {
        blackPlayer = make_unique<ComputerLevel1>(Colour::Black);
    } else if(black == "computer[2]") {
        blackPlayer = make_unique<ComputerLevel2>(Colour::Black);
    } else {
        blackPlayer = make_unique<ComputerLevel3>(Colour::Black);
    }
}

Board Game::getBoard() const {
	return board;
}

void Game::set(shared_ptr<Piece> p, int row, int col) {
    p->attach(board.getTD());
    p->attach(board.getGD());
    p->moveIn(row, col);
    if(p->getColour() == Colour::White) {
        whitePlayer->set(p);
    } else {
        blackPlayer->set(p);
    }
}

void Game::unset(int row, int col) {
    board.unset(row, col);
}

void Game::exitSetup() {
    board.validate();
    whitePlayer->exitSetup();
    blackPlayer->exitSetup();
}

void Game::init() {
    set(make_shared<Rook>(board.getCell(0, 0), Colour::Black), 0, 0);
    set(make_shared<Knight>(board.getCell(0, 0), Colour::Black), 0, 1);
    set(make_shared<Bishop>(board.getCell(0, 0), Colour::Black), 0, 2);
    set(make_shared<Queen>(board.getCell(0, 0), Colour::Black), 0, 3);
    set(make_shared<King>(board.getCell(0, 0), Colour::Black), 0, 4);
    set(make_shared<Bishop>(board.getCell(0, 0), Colour::Black), 0, 5);
    set(make_shared<Knight>(board.getCell(0, 0), Colour::Black), 0, 6);
    set(make_shared<Rook>(board.getCell(0, 0), Colour::Black), 0, 7);
    for(int i = 0; i < 8; i++) {
        set(make_shared<Pawn>(board.getCell(0, 0), Colour::Black), 1, i);
        set(make_shared<Pawn>(board.getCell(0, 0), Colour::White), 6, i);
    }
    set(make_shared<Rook>(board.getCell(0, 0), Colour::White), 7, 0);
    set(make_shared<Knight>(board.getCell(0, 0), Colour::White), 7, 1);
    set(make_shared<Bishop>(board.getCell(0, 0), Colour::White), 7, 2);
    set(make_shared<Queen>(board.getCell(0, 0), Colour::White), 7, 3);
    set(make_shared<King>(board.getCell(0, 0), Colour::White), 7, 4);
    set(make_shared<Bishop>(board.getCell(0, 0), Colour::White), 7, 5);
    set(make_shared<Knight>(board.getCell(0, 0), Colour::White), 7, 6);
    set(make_shared<Rook>(board.getCell(0, 0), Colour::White), 7, 7);
    cout << board;
}

void Game::checkState() {
    if(board.getWhiteCheckmate()) {
        cout << "Checkmate! Black Wins!" << endl;
        blackPlayer->updateGrade(1);
        board = Board{};
        whitePlayer->clearPieces();
        blackPlayer->clearPieces();
        init();
    }
    if(board.getBlackCheckmate()) {
        cout << "Checkmate! White Wins!" << endl;
        whitePlayer->updateGrade(1);
        board = Board{};
        whitePlayer->clearPieces();
        blackPlayer->clearPieces();
        init();
    }
    if(whitePlayer->checkStalement()) {
        if(board.getWhiteCheck()) {
            cout << "Checkmate! Black wins!" << endl;
            blackPlayer->updateGrade(1);
        } else {
            cout << "Stalemate!" << endl;
            whitePlayer->updateGrade(0.5);
            blackPlayer->updateGrade(0.5);
        }
            board = Board{};
            whitePlayer->clearPieces();
            blackPlayer->clearPieces();
            init();
    }
    if(blackPlayer->checkStalement()) {
        if(board.getBlackCheck()) {
            cout << "Checkmate! White wins!" << endl;
            whitePlayer->updateGrade(1);
        } else {
            cout << "Stalemate!" << endl;
            whitePlayer->updateGrade(0.5);
            blackPlayer->updateGrade(0.5);
        }
            board = Board{};
            whitePlayer->clearPieces();
            blackPlayer->clearPieces();
            init();
    }  
    if(board.getWhiteCheck()) {
        cout << "White is in check." << endl;
    }
    if(board.getBlackCheck()) {
        cout << "Black is in check." << endl;
    }
}

void Game::humanMove(int start_r, int start_c, int end_r, int end_c, Colour c) {
    if(c == Colour::White) {
        whitePlayer->move(start_r, start_c, end_r, end_c);
        cout << board;;
    } else {
        blackPlayer->move(start_r, start_c, end_r, end_c);
        cout << board;
    }
    previousMoves.push_back(newMove);
    checkState();
}

void Game::computerMove(Colour c) {
    if(c == Colour::White) {
        whitePlayer->move();
        cout << board;
    } else {
        blackPlayer->move();
        cout << board;
    }
    previousMoves.push_back(newMove);
    checkState();
}

void Game::resign(Colour c) {
    if(c == Colour::White) {
        cout << "Checkmate! Black Wins!" << endl;
        blackPlayer->updateGrade(1);
        board = Board{};
        whitePlayer->clearPieces();
        blackPlayer->clearPieces();
        init();
    } else {
        cout << "Checkmate! White Wins!" << endl;
        whitePlayer->updateGrade(1);
        board = Board{};
        whitePlayer->clearPieces();
        blackPlayer->clearPieces();
        init();
    }
}

void Game::undo() {
    int size = previousMoves.size();
    if(size != 0) {
        Move lastMove = previousMoves[size - 1];
        lastMove.lastMovedPiece->moveIn(lastMove.start_r, lastMove.start_c);
        if(lastMove.capturing) {
            lastMove.captured->moveIn(lastMove.end_r, lastMove.end_c);     
        }
        previousMoves.pop_back();
    }
}

void Game::endGame() {
    cout << "Final Score:" << endl;
    cout << "White: " << whitePlayer->getScore() << endl;
    cout << "Black: " << blackPlayer->getScore() << endl;
}
