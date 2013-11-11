#include "BangWrapper.hpp"

BangWrapper::BangWrapper(int x, int y, int direction, Bang * bang) :
  Wrapper(x,y,direction)
{
  this->bang = bang;
}

BangWrapper::~BangWrapper()
{
  delete bang;
}

int BangWrapper::move()
{
  return bang->move();
}

void BangWrapper::perform(int key, int value)
{
}

Wrapper * BangWrapper::breed()
{
  return NULL;
}

Bang * BangWrapper::getBang()
{
  return bang;
}

BITMAP * BangWrapper::getBuffer()
{
  return bang->getBuffer();
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
  return bang->getId();
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
  return bang->isDeath();
}

bool BangWrapper::isPerformer()
{
  return false;
}
