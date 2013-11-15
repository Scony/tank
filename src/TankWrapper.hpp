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

  bool isVisible();
  bool isDeath();
  bool isPerformer();
  bool isFocusable();

  int move();
  void perform(int key, int value);
  Wrapper * breed();
  void applyChanges();

  Tank * getTank();
  BITMAP * getBuffer();
  int getSize();
  int getSpeed();
  int getId();
  int getPower();
};

#endif
