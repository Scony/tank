#include "BulletWrapper.hpp"

BulletWrapper::BulletWrapper(int x, int y, int direction, Bullet * bullet) :
  Wrapper(x,y,direction)
{
  this->bullet = bullet;
  visible = true;
  death = false;
}

BulletWrapper::~BulletWrapper()
{
  delete bullet;
}

int BulletWrapper::move()
{
  return bullet->move();
}

void BulletWrapper::bang()
{
  visible = false;
  death = true;
}

Wrapper * BulletWrapper::breed()
{
  return NULL;
}

Bullet * BulletWrapper::getBullet()
{
  return bullet;
}

BITMAP * BulletWrapper::getBuffer()
{
  return bullet->getBuffer();
}

int BulletWrapper::getSize()	// todo
{
  return 8;
}

int BulletWrapper::getSpeed()	// todo
{
  return 2;
}

bool BulletWrapper::isVisible()	// todo
{
  return visible;
}

bool BulletWrapper::isDeath()
{
  if(death)
    return true;

  return bullet->isDeath();
}

bool BulletWrapper::isCollisionable() // todo
{
  return true;
}

bool BulletWrapper::isBangMaker() // todo
{
  return true;
}
