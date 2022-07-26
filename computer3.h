#ifndef _COMPUTER3_H_
#define _COMPUTER3_H_
#include "player.h"

class ComputerLevel3 : public Player{
        public:
        ComputerLevel3(Colour colour);
        void move(int, int, int, int) override;
        void move();
};

#endif
