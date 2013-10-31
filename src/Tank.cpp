#include "Tank.hpp"

Tank::Tank(Spriter * spriter, int speed)
{
  this->spriter = spriter;
  buffer = NULL;
  this->speed= speed;
}

Tank::~Tank()
{
}

BITMAP * Tank::getBuffer()
{
  return buffer;
}

int Tank::getSpeed()
{
  return speed;
}

int Tank::getSize()
{
  return spriter->getTankSize();
}
