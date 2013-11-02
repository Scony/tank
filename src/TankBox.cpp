#include "TankBox.hpp"

TankBox::TankBox(int x, int y, int direction, Tank * tank) :
  Box(x,y,direction)
{
  this->tank = tank;
}

TankBox::~TankBox()
{
}

Tank * TankBox::getTank()
{
  return tank;
}
