#ifndef PLAYER_2_TANK_HPP
#define PLAYER_2_TANK_HPP

#include "Tank.hpp"

class Player2Tank : public Tank
{
public:
  Player2Tank(Spriter * spriter);
  Player2Tank(Spriter * spriter, int rotation,
	      int hp, int hpMax,
	      int ammo, int ammoMax,
	      int fuel, int fuelMax,
	      int reload, int reloadMax);
  ~Player2Tank();

  int move();
};

#endif
