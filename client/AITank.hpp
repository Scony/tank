#ifndef AI_TANK_HPP
#define AI_TANK_HPP

#include "Tank.hpp"

class AITank : public Tank
{
  int intent;
  int length;
public:
  AITank(Spriter * spriter);
  AITank(Spriter * spriter, int rotation,
	 int hp, int hpMax,
	 int ammo, int ammoMax,
	 int fuel, int fuelMax,
	 int reload, int reloadMax);
  ~AITank();

  int move();

  int getId();
};

#endif
