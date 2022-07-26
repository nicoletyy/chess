#include "graphicsdisplay.h"
#include <string>
using namespace std;

GraphicsDisplay::GraphicsDisplay(): xwindow{500, 500}, gridSize{50} {
    for (int i = 0; i < 8; i++) {
        xwindow.drawBigString(40, i * 50 + 50, to_string(8 - i), 1);
    }
    for (char c = 'a'; c < 'i'; c++) {
        string s(1, c);
        xwindow.drawBigString(70 + (c - 'a') * 50, 450, s, 1);
    }
    for (int m = 0; m < 8; m++) {
        for (int n = 0; n < 8; n++) {
            if ((m + n) % 2 == 0) {
                xwindow.fillRectangle(50 + m * 50, n * 50 + 20, 50, 50, 0);
            } else {
                xwindow.fillRectangle(50 + m * 50, n * 50 + 20, 50, 50, 3);
            }
        }
    }
}

void GraphicsDisplay::notifyIn(Subject<Info> &whoNotified) {
    Info i = whoNotified.getInfo();
    if (i.pieceColour == Colour::White) {
        if ((i.col + i.row) % 2 == 0) {
            xwindow.fillRectangle(50 + i.col * 50, i.row * 50 + 20, 50, 50, 0);
        } else {
            xwindow.fillRectangle(50 + i.col * 50, i.row * 50 + 20, 50, 50, 3);
        }
        switch (i.pieceType){
          case 1:
            xwindow.drawBigString(i.col * 50 + 60, i.row * 50 + 40, "k", 1 );
          case 2:
            xwindow.drawBigString(i.col * 50 + 60, i.row * 50 + 40, "q", 1 );
          case 3:
            xwindow.drawBigString(i.col * 50 + 60, i.row * 50 + 40, "b", 1 );
          case 4:
            xwindow.drawBigString(i.col * 50 + 60, i.row * 50 + 40, "r", 1 );
          case 5:
            xwindow.drawBigString(i.col * 50 + 60, i.row * 50 + 40, "n", 1 );
          case 6:
            xwindow.drawBigString(i.col * 50 + 60, i.row * 50 + 40, "p", 1 );
	}
    } else if (i.pieceColour == Colour::Black) {
        if ((i.col + i.row) % 2 == 0) {
            xwindow.fillRectangle(50 + i.col * 50, i.row * 50 + 20, 50, 50, 0);
        } else {
            xwindow.fillRectangle(50 + i.col * 50, i.row * 50 + 20, 50, 50, 3);
        }
        switch (i.pieceType) {
          case 1:
            xwindow.drawBigString(i.col * 50 + 60, i.row * 50 + 40, "K", 1 );
          case 2:
            xwindow.drawBigString(i.col * 50 + 60, i.row * 50 + 40, "Q", 1 );
          case 3:
            xwindow.drawBigString(i.col * 50 + 60, i.row * 50 + 40, "B", 1 );
          case 4:
            xwindow.drawBigString(i.col * 50 + 60, i.row * 50 + 40, "R", 1 );
          case 5:
            xwindow.drawBigString(i.col * 50 + 60, i.row * 50 + 40, "N", 1 );
          case 6:
            xwindow.drawBigString(i.col * 50 + 60, i.row * 50 + 40, "P", 1 );
    	}
    } else {
        if ((i.col + i.row) % 2 == 0) {
            xwindow.fillRectangle(50 + i.col * 50, i.row * 50 + 20, 50, 50, 0);
        } else {
            xwindow.fillRectangle(50 + i.col * 50, i.row * 50 + 20, 50, 50, 3);
        }
    }
}

void GraphicsDisplay::notifyOut(Subject<Info> &whoNotified) {};

GraphicsDisplay::~GraphicsDisplay() {}

