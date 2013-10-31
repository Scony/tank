#ifndef AI_TANK_HPP
#define AI_TANK_HPP

#include "Tank.hpp"

class AITank : public Tank
{
  int offset;
  int intent;
  int length;
public:
  AITank(Spriter * spriter, int speed);
  ~AITank();

  int move();
};

#endif
