#include "Consumable.hpp"

Consumable::Consumable(Spriter * spriter, int amount)
{
  this->spriter = spriter;
  buffer = NULL;

  this->amount = amount;
  blink = 0;
  blinkMax = 30;
}

Consumable::~Consumable()
{
}

void Consumable::update()
{
  blink = (blink + 1) % blinkMax;
}

int Consumable::consume()
{
  int tmp = amount;
  amount = 0;

  return tmp;
}

int Consumable::getId()
{
  return 16;
}

BITMAP * Consumable::getBuffer()
{
  return buffer;
}

bool Consumable::isDeath()
{
  return amount ? false : true;
}
