#ifndef PLAYER_TANK_HPP
#define PLAYER_TANK_HPP

#include "Tank.hpp"

class PlayerTank : public Tank
{
  int offset;
public:
  PlayerTank(Spriter * spriter, int speed);
  ~PlayerTank();

  int move();
};

#endif
