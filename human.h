#ifndef _HUMAN_H_
#define _HUMAN_H_
#include "player.h"

class Human : public Player {
	public:
	Human(Colour colour);
	void move(int, int, int, int) override;
};

#endif
