#include "BulletWrapper.hpp"
#include "BangWrapper.hpp"
#include "LittleBang.hpp"

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
  if(death)
    return new BangWrapper(x-12,y-12,1,new LittleBang(bullet->getSpriter()));

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

int BulletWrapper::getId()
{
  return bullet->getId();
}

int BulletWrapper::getResistance()
{
  return 0;
}

int BulletWrapper::getPower()
{
  return bullet->getPower();
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
