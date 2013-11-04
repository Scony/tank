#include "TankWrapper.hpp"

TankWrapper::TankWrapper(int x, int y, int direction, Tank * tank) :
  Wrapper(x,y,direction)
{
  this->tank = tank;
}

TankWrapper::~TankWrapper()
{
  delete tank;
}

int TankWrapper::move()
{
  return tank->move();
}

Tank * TankWrapper::getTank()
{
  return tank;
}

BITMAP * TankWrapper::getBuffer()
{
  return tank->getBuffer();
}

int TankWrapper::getSize()	// todo
{
  return 32;
}

int TankWrapper::getSpeed()	// todo
{
  return 1;
}

bool TankWrapper::isClerable()	// todo
{
  return true;
}

bool TankWrapper::isDeath()	// todo
{
  return false;
}

bool TankWrapper::isCollisionable() // todo
{
  return true;
}
