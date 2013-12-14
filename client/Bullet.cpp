#include "Bullet.hpp"

Bullet::Bullet(Spriter * spriter)
{
  this->spriter = spriter;
  buffer = NULL;
}

Bullet::~Bullet()
{
}

BITMAP * Bullet::getBuffer()
{
  return buffer;
}

Spriter * Bullet::getSpriter()
{
  return spriter;
}

int Bullet::getId()
{
  return 9;
}
