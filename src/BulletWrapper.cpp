#include "BulletWrapper.hpp"

BulletWrapper::BulletWrapper(int x, int y, int direction, Bullet * bullet) :
  Wrapper(x,y,direction)
{
  this->bullet = bullet;
}

BulletWrapper::~BulletWrapper()
{
}

int BulletWrapper::move()
{
  return bullet->move();
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

bool BulletWrapper::isClerable()	// todo
{
  return true;
}

bool BulletWrapper::isDeath()	// todo
{
  return false;
}

bool BulletWrapper::isCollisionable() // todo
{
  return true;
}
