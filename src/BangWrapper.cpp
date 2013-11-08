#include "BangWrapper.hpp"

BangWrapper::BangWrapper(int x, int y, int direction, Bang * bng) :
  Wrapper(x,y,direction)
{
  this->bng = bng;
}

BangWrapper::~BangWrapper()
{
  delete bng;
}

int BangWrapper::move()
{
  return bng->move();
}

void BangWrapper::bang()
{
}

Wrapper * BangWrapper::breed()
{
  return NULL;
}

Bang * BangWrapper::getBang()
{
  return bng;
}

BITMAP * BangWrapper::getBuffer()
{
  return bng->getBuffer();
}

int BangWrapper::getSize()	// todo
{
  return 32;
}

int BangWrapper::getSpeed()
{
  return 0;
}

int BangWrapper::getId()
{
  return bng->getId();
}

int BangWrapper::getResistance()
{
  return 0;
}

int BangWrapper::getPower()
{
  return 0;
}

bool BangWrapper::isVisible()
{
  return true;
}

bool BangWrapper::isDeath()
{
  return bng->isDeath();
}

bool BangWrapper::isBangMaker()
{
  return false;
}
