#include "LineBullet.hpp"

LineBullet::LineBullet(Spriter * spriter, int intent) :
  Bullet(spriter)
{
  buffer = spriter->getBullet(intent-1);
  this->intent = intent;
  lifetime = 60;
}

LineBullet::~LineBullet()
{
}

int LineBullet::move()
{
  lifetime--;
  return intent;
}

int LineBullet::getId()
{
  return 10;
}

bool LineBullet::isDeath()
{
  if(!lifetime)
    return true;

  return false;
}
