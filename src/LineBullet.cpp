#include "LineBullet.hpp"

LineBullet::LineBullet(Spriter * spriter, int intent) :
  Bullet(spriter)
{
  buffer = spriter->getBullet(intent);
  this->intent = intent;
}

LineBullet::~LineBullet()
{
}

int LineBullet::move()
{
  return intent;
}
