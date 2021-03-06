#include <math.h>

#include "TankWrapper.hpp"
#include "BulletWrapper.hpp"
#include "BangWrapper.hpp"
#include "SimpleBang.hpp"
#include "WreckTank.hpp"
#include "Configuration.hpp"

TankWrapper::TankWrapper(int x, int y, int direction, Tank * tank) :
  Wrapper(x,y,direction)
{
  this->tank = tank;
}

TankWrapper::~TankWrapper()
{
  delete tank;
}

int TankWrapper::move()
{
  return tank->move();
}

void TankWrapper::perform(int key, int value)
{
  switch(key)
    {
    case 17:
      tank->addAmmo(value);
      break;
    case 18:
      tank->addFuel(value);
      break;
    default:
      tank->hurt(value);
    }
}

Wrapper * TankWrapper::breed()
{
  if(tank->isDeath())
    return new TankWrapper(x,y,1,new WreckTank(tank->getSpriter()));

  if(tank->isBurning())
    return new BangWrapper(x,y,1,new SimpleBang(tank->getSpriter()));

  Bullet * bullet = tank->breed();
  if(bullet)
    {
      int bx;
      int by;
      int bdirection = tank->getRotation();

      // load magic numbers
      int medium = Configuration::getInstance()->getMedium();
      int small = Configuration::getInstance()->getSmall();

      // correction to avoid seppuku
      int cx = round((double)x / medium) * medium;
      int cy = round((double)y / medium) * medium;
      int magicOffset = 2;

      switch(bdirection)
	{
	case 1:
	  bx = x + ((getSize() - small) / 2);
	  by = (cy < y ? cy : y) - small - magicOffset;
	  break;
	case 2:
	  bx = (cx > x ? cx : x) + getSize() + magicOffset;
	  by = y + ((getSize() - small) / 2);
	  break;
	case 3:
	  bx = x + ((getSize() - small) / 2);
	  by = (cy > y ? cy : y) + getSize() + magicOffset;
	  break;
	case 4:
	  bx = (cx < x ? cx : x) - small - magicOffset;
	  by = y + ((getSize() - small) / 2);
	}

      return new BulletWrapper(bx,by,bdirection,bullet);
    }

  return NULL;
}

void TankWrapper::applyChanges()
{
  int ox = getX();
  int oy = getY();

  Wrapper::applyChanges();

  tank->burnFuel(abs(ox-getX())+abs(oy-getY()));
}

Tank * TankWrapper::getTank()
{
  return tank;
}

BITMAP * TankWrapper::getBuffer()
{
  return tank->getBuffer();
}

int TankWrapper::getSize()
{
  return Configuration::getInstance()->getBig();
}

int TankWrapper::getSpeed()
{
  return 1;
}

int TankWrapper::getId()
{
  return tank->getId();
}

int TankWrapper::getPower()
{
  return 0;
}

bool TankWrapper::isVisible()
{
  return true;
}

bool TankWrapper::isDeath()
{
  return tank->isDeath();
}

bool TankWrapper::isPerformer()
{
  return false;
}

bool TankWrapper::isFocusable()
{
  return true;
}
