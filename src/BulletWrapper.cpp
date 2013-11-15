#include "BulletWrapper.hpp"
#include "BangWrapper.hpp"
#include "LittleBang.hpp"
#include "Configuration.hpp"

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

void BulletWrapper::perform(int key, int value)
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

int BulletWrapper::getSize()
{
  return Configuration::getInstance()->getSmall();
}

int BulletWrapper::getSpeed()
{
  return 2;
}

int BulletWrapper::getId()
{
  return bullet->getId();
}

int BulletWrapper::getPower()
{
  return bullet->getPower();
}

bool BulletWrapper::isVisible()
{
  return visible;
}

bool BulletWrapper::isDeath()
{
  if(death)
    return true;

  return bullet->isDeath();
}

bool BulletWrapper::isPerformer()
{
  return true;
}

bool BulletWrapper::isFocusable()
{
  return false;
}
