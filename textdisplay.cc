
#include <string>

#include "textdisplay.h"
using namespace std;

//odd :_ _ _ _
//even: _ _ _ _
TextDisplay::TextDisplay() {
    vector<char> odd;
    vector<char> even;
    for (int i = 0; i < 8; i++) {
        if (i % 2 == 0) {
            odd.emplace_back('_');
            even.emplace_back(' ');
        } else {
            odd.emplace_back(' ');
            even.emplace_back('_');
        }
    }
    for (int j = 0; j < 8; j++) {
        if (j % 2 == 0) {
            textDisplay.emplace_back(even);
        } else {
            textDisplay.emplace_back(odd);
        }
    }
}

void TextDisplay::notifyIn(Subject<Info> &whoNotified) {
    Info i = whoNotified.getInfo();
    int r = i.row;
    int c = i.col;
    int type = i.pieceType;
    if (i.pieceColour == Colour::White) {
        if (type == 1) {
            textDisplay[r][c] = 'K';
        } else if (type == 2) {
            textDisplay[r][c] = 'Q';
        } else if (type == 3) {
            textDisplay[r][c] = 'B';
        } else if (type == 4) {
            textDisplay[r][c] = 'R';
        } else if (type == 5) {
            textDisplay[r][c] = 'N';
        } else if (type == 6) {
            textDisplay[r][c] = 'P';
        } 
    } else if (i.pieceColour == Colour::Black) {
        if (type == 1) {
            textDisplay[r][c] = 'k';
        } else if (type == 2) {
            textDisplay[r][c] = 'q';
        } else if (type == 3) {
            textDisplay[r][c] = 'b';
        } else if (type == 4) {
            textDisplay[r][c] = 'r';
        } else if (type == 5) {
            textDisplay[r][c] = 'n';
        } else if (type == 6) {
            textDisplay[r][c] = 'p';
        } 
    }
}

void TextDisplay::notifyOut(Subject<Info> &whoNotified) {
	Info i = whoNotified.getInfo();
        int r = i.row;
        int c = i.col;
	if ((r + c) % 2 == 0) {
            textDisplay[r][c] = ' ';
        } else {
            textDisplay[r][c] = '_';
        }
} 

ostream &operator<<(ostream &out, const TextDisplay &td) {
    for (int i = 0; i < 8; i++) {
        out << 8 - i << " ";
        for (int j = 0; j < 8; j++) {
            out << td.textDisplay[i][j];
        }
	out << endl;
    }
    out << endl << " ";
    for (char i = 'a'; i < ('h' + 1); ++i) {
        out << i;
    }
	out << endl;
	return out;
}



