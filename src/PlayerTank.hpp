#ifndef PLAYER_TANK_HPP
#define PLAYER_TANK_HPP

#include "Tank.hpp"

class PlayerTank : public Tank
{
public:
  PlayerTank(Spriter * spriter);
  PlayerTank(Spriter * spriter, int rotation,
	     int hp, int hpMax,
	     int ammo, int ammoMax,
	     int fuel, int fuelMax,
	     int reload, int reloadMax);
  ~PlayerTank();

  int move();
  int getId();
};

#endif
