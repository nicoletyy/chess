#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <vector>
#include <memory>
#include "piece.h"
using namespace std;

class Player {
	Colour colour;
	float grade;
	protected:
	vector<shared_ptr<Piece>> pieces;

	public:
	Player(Colour c, float grade);
	virtual void move(int, int, int, int) = 0;
	virtual void move();
	void updateGrade(float);
	void set(shared_ptr<Piece>);
	// delete all removed pieces at the end of setup mode
	void exitSetup();
	void clearPieces();
	bool checkStalement();
	float getScore();
};

#endif
