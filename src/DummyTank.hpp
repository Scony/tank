#ifndef DUMMY_TANK_HPP
#define DUMMY_TANK_HPP

#include "Tank.hpp"

class DummyTank : public Tank
{
public:
  DummyTank(Spriter * spriter, int speed);
  ~DummyTank();

  int move();
};

#endif
