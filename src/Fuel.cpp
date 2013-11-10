#include "Fuel.hpp"

Fuel::Fuel(Spriter * spriter, int amount) :
  Consumable(spriter,amount)
{
  buffer = spriter->getConsumable(0);

  blank = false;
}

Fuel::~Fuel()
{
}

int Fuel::move()
{
  update();

  if(!blink)
    {
      buffer = blank ? spriter->getConsumable(0) : spriter->getBlank();
      blank = !blank;
    }

  return 0;
}

int Fuel::getId()
{
  return 18;
}
