#ifndef PLAYER_2_TANK_HPP
#define PLAYER_2_TANK_HPP

#include "Tank.hpp"

class Player2Tank : public Tank
{
  int offset;
public:
  Player2Tank(Spriter * spriter);
  ~Player2Tank();

  int move();
};

#endif
