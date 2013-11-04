#ifndef PLAYER_TANK_HPP
#define PLAYER_TANK_HPP

#include "Tank.hpp"

class PlayerTank : public Tank
{
  int offset;
  int rotation;
  int reload;
  Bullet * born;
public:
  PlayerTank(Spriter * spriter);
  ~PlayerTank();

  int move();
  Bullet * breed();
  int getRotation();
};

#endif
