#include <math.h>

#include "TankWrapper.hpp"
#include "BulletWrapper.hpp"
// #include "BangWrapper.hpp"
// #include "SimpleBang.hpp"
#include "WreckTank.hpp"

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

void TankWrapper::bang()
{
  tank->hurt(1);
}

Wrapper * TankWrapper::breed()
{
  if(tank->isDeath())
    return new TankWrapper(x,y,1,new WreckTank(tank->getSpriter()));
    // return new BangWrapper(x,y,1,new SimpleBang(tank->getSpriter()));

  Bullet * bullet = tank->breed();
  if(bullet)
    {
      int bx;
      int by;
      int bdirection = tank->getRotation();

      // correction to avoid seppuku
      int cx = round((double)x / 16) * 16;
      int cy = round((double)y / 16) * 16;
      int magicOffset = 2;

      switch(bdirection)	// todo: hardcodes
	{
	case 1:
	  bx = x + ((getSize() - 8) / 2);
	  by = (cy < y ? cy : y) - 8 - magicOffset;
	  break;
	case 2:
	  bx = (cx > x ? cx : x) + getSize() + magicOffset;
	  by = y + ((getSize() - 8) / 2);
	  break;
	case 3:
	  bx = x + ((getSize() - 8) / 2);
	  by = (cy > y ? cy : y) + getSize() + magicOffset;
	  break;
	case 4:
	  bx = (cx < x ? cx : x) - 8 - magicOffset;
	  by = y + ((getSize() - 8) / 2);
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
  return 32;
}

int TankWrapper::getSpeed()
{
  return 1;
}

int TankWrapper::getId()
{
  return tank->getId();
}

int TankWrapper::getResistance()
{
  return 0;
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

bool TankWrapper::isBangMaker()
{
  return false;
}
