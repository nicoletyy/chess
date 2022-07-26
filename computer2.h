#ifndef _COMPUTER2_H_
#define _COMPUTER2_H_
#include "player.h"

class ComputerLevel2 : public Player{
        public:
        ComputerLevel2(Colour colour);
        void move(int, int, int, int) override;
        void move();
};

#endif
