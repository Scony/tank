#ifndef TANK_BOX_HPP
#define TANK_BOX_HPP

#include "Tank.hpp"

class TankBox
{
  // actual values
  int x;
  int y;
  int direction;

  // changes to apply or reset
  int nx;
  int ny;
  int ndirection;

  Tank * tank;
public:
  TankBox(int x, int y, int direction, Tank * tank);
  ~TankBox();

  void resetChanges();
  void applyChanges();

  int getX();
  int getY();
  int getDirection();
  Tank * getTank();

  int getNewX();
  void setNewX(int x);
  int getNewY();
  void setNewY(int y);
  int getNewDirection();
  void setNewDirection(int direction);
};

#endif
