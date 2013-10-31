#include "Tank.hpp"

Tank::Tank(Spriter * spriter)
{
  this->spriter = spriter;
  buffer = NULL;
}

Tank::~Tank()
{
}

BITMAP * Tank::getBuffer()
{
  return buffer;
}

int Tank::getSize()
{
  return spriter->getTankSize();
}
