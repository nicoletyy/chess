#ifndef _GAME_H_
#define _GAME_H_
#include <vector>
#include <memory>
#include "board.h"
#include "player.h"
#include "move.h"

using namespace std;

class Game {
    unique_ptr<Player> whitePlayer, blackPlayer;
    Board board;
    vector<Move> previousMoves;
    public:
    Game(string, string);
    Board getBoard() const;
    void set(shared_ptr<Piece>, int, int);
    void unset(int, int);
    void exitSetup();
    void init();
    void checkState();
    void humanMove(int, int, int, int, Colour);
    void computerMove(Colour);
    void resign(Colour);
    void undo();
    void endGame();
};

#endif
