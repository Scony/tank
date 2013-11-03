#include "Wrapper.hpp"

Wrapper::Wrapper(int x, int y, int direction)
{
  this->x = x;
  this->y = y;
  this->direction = direction;
  
  resetChanges();
}

Wrapper::~Wrapper()
{
}

void Wrapper::resetChanges()
{
  nx = x;
  ny = y;
  ndirection = direction;
}

void Wrapper::applyChanges()
{
  x = nx;
  y = ny;
  direction = ndirection;
}

int Wrapper::getX()
{
  return x;
}

int Wrapper::getY()
{
  return y;
}

int Wrapper::getDirection()
{
  return direction;
}

int Wrapper::getNewX()
{
  return nx;
}

void Wrapper::setNewX(int x)
{
  nx = x;
}

int Wrapper::getNewY()
{
  return ny;
}

void Wrapper::setNewY(int y)
{
  ny = y;
}

int Wrapper::getNewDirection()
{
  return ndirection;
}

void Wrapper::setNewDirection(int direction)
{
  ndirection = direction;
}
