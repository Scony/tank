#include "Tank.hpp"

Tank::Tank(Spriter * spriter)
{
  this->spriter = spriter;
  buffer = NULL;
}

Tank::~Tank()
{
}

Bullet * Tank::breed()
{
  return NULL;
}

BITMAP * Tank::getBuffer()
{
  return buffer;
}

int Tank::getSize()
{
  return spriter->getTankSize();
}
