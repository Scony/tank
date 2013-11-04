#ifndef TANK_WRAPPER_HPP
#define TANK_WRAPPER_HPP

#include "Wrapper.hpp"
#include "Tank.hpp"

class TankWrapper : public Wrapper
{
  Tank * tank;
public:
  TankWrapper(int x, int y, int direction, Tank * tank);
  ~TankWrapper();

  int move();

  Tank * getTank();
  BITMAP * getBuffer();
  int getSize();
  int getSpeed();

  bool isClerable();
  bool isDeath();
  bool isCollisionable();
};

#endif
