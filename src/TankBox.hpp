#ifndef TANK_BOX_HPP
#define TANK_BOX_HPP

#include "Box.hpp"
#include "Tank.hpp"

class TankBox : public Box
{
  Tank * tank;
public:
  TankBox(int x, int y, int direction, Tank * tank);
  ~TankBox();

  Tank * getTank();
};

#endif
