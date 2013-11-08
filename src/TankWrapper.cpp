#include "TankWrapper.hpp"
#include "BulletWrapper.hpp"
#include "BangWrapper.hpp"
#include "SimpleBang.hpp"

TankWrapper::TankWrapper(int x, int y, int direction, Tank * tank) :
  Wrapper(x,y,direction)
{
  this->tank = tank;
  forceDeath = false;
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
  forceDeath = true;
}

Wrapper * TankWrapper::breed()
{
  if(forceDeath)
    {
      forceDeath = false;
      return new BangWrapper(x,y,1,new SimpleBang(tank->getSpriter()));
    }

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

Tank * TankWrapper::getTank()
{
  return tank;
}

BITMAP * TankWrapper::getBuffer()
{
  return tank->getBuffer();
}

int TankWrapper::getSize()	// todo
{
  return 32;
}

int TankWrapper::getSpeed()	// todo
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

bool TankWrapper::isVisible()	// todo
{
  return true;
}

bool TankWrapper::isDeath()	// todo
{
  return false;
}

bool TankWrapper::isCollisionable() // todo
{
  return true;
}

bool TankWrapper::isBangMaker() // todo
{
  return false;
}
