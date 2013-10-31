#include "TankBox.hpp"

TankBox::TankBox(int x, int y, int direction, Tank * tank)
{
  this->x = x;
  this->y = y;
  this->direction = direction;
  
  resetChanges();

  this->tank = tank;
}

TankBox::~TankBox()
{
}

void TankBox::resetChanges()
{
  nx = x;
  ny = y;
  ndirection = direction;
}

void TankBox::applyChanges()
{
  x = nx;
  y = ny;
  direction = ndirection;
}

int TankBox::getX()
{
  return x;
}

int TankBox::getY()
{
  return y;
}

int TankBox::getDirection()
{
  return direction;
}

Tank * TankBox::getTank()
{
  return tank;
}

int TankBox::getNewX()
{
  return nx;
}

void TankBox::setNewX(int x)
{
  nx = x;
}

int TankBox::getNewY()
{
  return ny;
}

void TankBox::setNewY(int y)
{
  ny = y;
}

int TankBox::getNewDirection()
{
  return ndirection;
}

void TankBox::setNewDirection(int direction)
{
  ndirection = direction;
}
