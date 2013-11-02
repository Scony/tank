#include "Box.hpp"

Box::Box(int x, int y, int direction)
{
  this->x = x;
  this->y = y;
  this->direction = direction;
  
  resetChanges();
}

Box::~Box()
{
}

void Box::resetChanges()
{
  nx = x;
  ny = y;
  ndirection = direction;
}

void Box::applyChanges()
{
  x = nx;
  y = ny;
  direction = ndirection;
}

int Box::getX()
{
  return x;
}

int Box::getY()
{
  return y;
}

int Box::getDirection()
{
  return direction;
}

int Box::getNewX()
{
  return nx;
}

void Box::setNewX(int x)
{
  nx = x;
}

int Box::getNewY()
{
  return ny;
}

void Box::setNewY(int y)
{
  ny = y;
}

int Box::getNewDirection()
{
  return ndirection;
}

void Box::setNewDirection(int direction)
{
  ndirection = direction;
}
