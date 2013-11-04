#include "BulletWrapper.hpp"

BulletWrapper::BulletWrapper(int x, int y, int direction, Bullet * bullet) :
  Wrapper(x,y,direction)
{
  this->bullet = bullet;
}

BulletWrapper::~BulletWrapper()
{
  delete bullet;
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

int BulletWrapper::getSpeed()	// todo
{
  return 2;
}

bool BulletWrapper::isClerable()	// todo
{
  return true;
}

bool BulletWrapper::isDeath()
{
  return bullet->isDeath();
}

bool BulletWrapper::isCollisionable() // todo
{
  return true;
}
