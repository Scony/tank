#include "TankWrapper.hpp"
#include "BulletWrapper.hpp"
#include "BangWrapper.hpp"
#include "SimpleBang.hpp"

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
    return new BangWrapper(x,y,1,new SimpleBang(tank->getSpriter()));

  Bullet * bullet = tank->breed();
  if(bullet)
    {
      int bx;
      int by;
      int bdirection = tank->getRotation();

      switch(bdirection)	// todo: hardcodes
	{
	case 1:
	  bx = x + ((getSize() - 8) / 2);
	  by = y - 8;
	  break;
	case 2:
	  bx = x + getSize();
	  by = y + ((getSize() - 8) / 2);
	  break;
	case 3:
	  bx = x + ((getSize() - 8) / 2);
	  by = y + getSize();
	  break;
	case 4:
	  bx = x - 8;
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
