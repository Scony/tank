#include "LineBullet.hpp"

LineBullet::LineBullet(Spriter * spriter, int intent) :
  Bullet(spriter)
{
  buffer = spriter->getBullet(intent-1);
  this->intent = intent;
}

LineBullet::~LineBullet()
{
}

int LineBullet::move()
{
  return intent;
}
