#ifndef _COMPUTER1_H_
#define _COMPUTER1_H_
#include "player.h"

class ComputerLevel1 : public Player{
	public:
	ComputerLevel1(Colour colour);
    void move(int, int, int, int) override;
	void move();
};

#endif
