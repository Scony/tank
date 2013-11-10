#include <math.h>

#include "ConsumableWrapper.hpp"
#include "BangWrapper.hpp"
#include "SimpleBang.hpp"

ConsumableWrapper::ConsumableWrapper(int x, int y, int direction, Consumable * consumable) :
  Wrapper(x,y,direction)
{
  this->consumable = consumable;
}

ConsumableWrapper::~ConsumableWrapper()
{
  delete consumable;
}

int ConsumableWrapper::move()
{
  return consumable->move();
}

void ConsumableWrapper::perform(int key, int value)
{
}

Wrapper * ConsumableWrapper::breed()
{
  return NULL;
}

BITMAP * ConsumableWrapper::getBuffer()
{
  return consumable->getBuffer();
}

int ConsumableWrapper::getSize()
{
  return 32;
}

int ConsumableWrapper::getSpeed()
{
  return 0;
}

int ConsumableWrapper::getId()
{
  return consumable->getId();
}

int ConsumableWrapper::getResistance()
{
  return 0;
}

int ConsumableWrapper::getPower()
{
  return consumable->consume();
}

bool ConsumableWrapper::isVisible()
{
  return true;
}

bool ConsumableWrapper::isDeath()
{
  return consumable->isDeath();
}

bool ConsumableWrapper::isBangMaker()
{
  return true;
}
