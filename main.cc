#include <iostream>
#include <string>
#include <memory>
#include "board.h"
#include "window.h"
#include "graphicsdisplay.h"
#include "textdisplay.h"
#include "game.h"
#include "piece.h"
#include "king.h"
#include "rook.h"
#include "knight.h"
#include "queen.h"
#include "pawn.h"
#include "bishop.h"
#include <locale>
#include <cctype>
using namespace std;

// helper functions

string tolower(string s) {
	for (int i = 0; i < (int) s.length(); i++) {
		if ((s[i] >= 'A') && (s[i] <= 'Z')) {
			s[i] = s[i] + 'a' - 'A';
		}
	}
	return s;
}

bool checkPieceType(string pieceType) {
    string type = tolower(pieceType);
    if (type == "k" || type == "q" || type == "b" || type == "r" || type == "n" || type == "p") {
        return true;
    } else {
        return false;
    }

}

bool checkLocation(string loc) {
    if (loc.length() != 2) {
        return false;
    }
    if (loc.substr(0, 1) < "a" || loc.substr(0, 1) > "h") {
        return false;
    }
    if (loc.substr(1, 2) < "1" || loc.substr(1, 2) > "8") {
        return false;
    }
    return true;
}

std::shared_ptr<Piece> makePiece(string pieceType, Game &g) {
    if (pieceType == "K") {
        shared_ptr<Piece> piece = make_shared<King>(g.getBoard().getCell(0, 0), Colour::White);
        return piece;
    } else if (pieceType == "k") {
        shared_ptr<Piece> piece = make_shared<King>(g.getBoard().getCell(0, 0), Colour::Black);
        return piece;
    } else if (pieceType == "Q") {
        shared_ptr<Piece> piece = make_shared<Queen>(g.getBoard().getCell(0, 0), Colour::White);
        return piece;
    } else if (pieceType == "q") {
        shared_ptr<Piece> piece = make_shared<Queen>(g.getBoard().getCell(0, 0), Colour::Black);
        return piece;
    } else if (pieceType == "R") {
        shared_ptr<Piece> piece = make_shared<Rook>(g.getBoard().getCell(0, 0),Colour::White);
        return piece;
    } else if (pieceType == "r") {
        shared_ptr<Piece> piece = make_shared<Rook>(g.getBoard().getCell(0, 0),Colour::Black);
        return piece;
    } else if (pieceType == "N") {
        shared_ptr<Piece> piece = make_shared<Knight>(g.getBoard().getCell(0, 0),Colour::White);
        return piece;
    } else if (pieceType == "n") {
        shared_ptr<Piece> piece = make_shared<Knight>(g.getBoard().getCell(0, 0),Colour::Black);
        return piece;
    } else if (pieceType == "P") {
        shared_ptr<Piece> piece = make_shared<Pawn>(g.getBoard().getCell(0, 0),Colour::White);
        return piece;
    } else if (pieceType == "p") {
        shared_ptr<Piece> piece = make_shared<Pawn>(g.getBoard().getCell(0, 0),Colour::Black);
        return piece;
    } else if (pieceType == "B") {
        shared_ptr<Piece> piece = make_shared<Bishop>(g.getBoard().getCell(0, 0),Colour::White);
        return piece;
    } else if (pieceType == "b") {
        shared_ptr<Piece> piece = make_shared<Bishop>(g.getBoard().getCell(0, 0),Colour::Black);
        return piece;
    } else {
	    return nullptr;
    }
}

bool isHuman(string player) {
    if (player.length() == 5) {
        return true;
    } 
    return false;
}

// global variables
bool promotion = false;
Move newMove {shared_ptr<Piece>(nullptr),
       	0, 0, 0 ,0, false, shared_ptr<Piece>(nullptr)};

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  bool whiteToGO = true;
  string p1White, p2Black;
  while (true) {
      cin >> cmd;
      if (cmd == "game") {
          cin >> p1White >> p2Black;
          break;
      }
  }
  Game g {p1White, p2Black};
  g.init();
  try {
      while (cin >> cmd) {
          if (cmd == "setup") {
              cout << "Setup gets started..." << endl;
              string s1,s2,s3;
              cin >> s1;
              if (s1 == "+") {
                  cin >> s2 >> s3;
                  if (checkLocation(s3) && checkPieceType(s2)) {
                      int r = 8 - stoi(s3.substr(1,2));
                      int c = s3[0] - 'a';
		      cout << "Reach hwwwe" << endl;
                      g.set(makePiece(s2, g), r, c);
                      cout << g.getBoard() << endl;
                  } else {
                          cout << "Invalid Placement. You cannot place " << s2 << "on";
                          cout << s3 << ". Please try again." << endl;
                          continue;
                  }
              } else if (s1 == "-") {
                      cin >> s2;
                      if (!(checkLocation(s2))) {
                              cout << "Invalid set.Please try again" << endl;
   			      continue;			      
                      }
                      int r = 8 - stoi(s2.substr(1,2));
                      int c = s2[0] - 'a';
                      g.unset(r, c);
                      cout << g.getBoard() << endl;
              } else if (s1 == "=") {
                      cin >> s2;
                      if (tolower(s2) == "black") {
                          cout << "Set black player to go." << endl;
                          whiteToGO = false;
                      } else if (tolower(s2) == "white") {
                          cout << "Set white player to go." << endl;
                          whiteToGO = true;
                      }
              } else if (s1 == "done") {
                      try {
                          g.exitSetup();
                      } catch(const char* msg) {
                          cout << msg << endl;
                          continue;
                      }    
              }
          } else if (cmd == "resign") {
              if (whiteToGO) {
                  g.resign(Colour::White);
              } else {
                  g.resign(Colour::Black);
              }
          } else if (cmd == "move") {          
              if (whiteToGO) {
                  if (isHuman(p1White)== true) {
                      string from, to;
                      cin >> from >> to;
                      if (checkLocation(from) && checkLocation(to)) {
                          int rowFrom = 8 - stoi(from.substr(1,2));
                          int colFrom = from[0] - 'a';
                          int rowTo = 8 - stoi(to.substr(1,2));
                          int colTo = to[0] - 'a';
                          g.humanMove(rowFrom, colFrom, rowTo, colTo, Colour::White);
                          if (promotion) {
                              string type;
                              cin >> type;
                              g.set(makePiece(type, g), rowTo, colTo);
                          }
                          whiteToGO = false;
                      } else {
                          whiteToGO = true;
                          cout << "Invalid Move. Please try again." << endl;
                      }
                  } else {
		      try {		  
                          g.computerMove(Colour::White);
		      } catch (InvalidMove i) {
			  whiteToGO = true;
	              }
                      whiteToGO = false;
                  }         
              } else {
                  if (isHuman(p2Black)== true) {
                      string from, to;
                      cin >> from >> to;
                      if (checkLocation(from) && checkPieceType(to)) {
                          int rowFrom = 8 - stoi(from.substr(1,2));
                          int colFrom = from[0] - 'a';
                          int rowTo = 8 - stoi(to.substr(1,2));
                          int colTo = to[0] - 'a';
                          g.humanMove(rowFrom, colFrom, rowTo, colTo, Colour::Black);
                          if (promotion) {
                              string type;
                              cin >> type;
                              g.set(makePiece(type, g), rowTo, colTo);
                          }
                          whiteToGO = true;
                      } else {
                          whiteToGO = false;
                          cout << "Invalid Move. Please try again." << endl;
                      }
                  } else {
		      try {
                      	g.computerMove(Colour::Black);
		      } catch (InvalidMove) {
			      whiteToGO = false;
		      }
                      whiteToGO = true;
                  }
              }
              cout << g.getBoard() << endl;
              newMove.lastMovedPiece = shared_ptr<Piece>(nullptr);
              newMove.captured = shared_ptr<Piece>(nullptr);
              newMove.capturing = false;
          } else if (cmd == "undo") {
	      g.undo();
    	      cout << g.getBoard() << endl;
	  }	      
      }
  } catch (ios::failure &e) { 
      g.endGame();
  }
  return 0;
}

