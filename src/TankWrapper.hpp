#ifndef TANK_WRAPPER_HPP
#define TANK_WRAPPER_HPP

#include "Wrapper.hpp"
#include "Tank.hpp"

class TankWrapper : public Wrapper
{
  Tank * tank;
  bool forceDeath;
public:
  TankWrapper(int x, int y, int direction, Tank * tank);
  ~TankWrapper();

  int move();
  void bang();
  Wrapper * breed();

  Tank * getTank();
  BITMAP * getBuffer();
  int getSize();
  int getSpeed();
  int getId();
  int getResistance();
  int getPower();

  bool isVisible();
  bool isDeath();
  bool isCollisionable();
  bool isBangMaker();
};

#endif
