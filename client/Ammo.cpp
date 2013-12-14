#include "Ammo.hpp"

Ammo::Ammo(Spriter * spriter, int amount) :
  Consumable(spriter,amount)
{
  buffer = spriter->getConsumable(1);

  blank = false;
}

Ammo::~Ammo()
{
}

int Ammo::move()
{
  update();

  if(!blink)
    {
      buffer = blank ? spriter->getConsumable(1) : spriter->getBlank();
      blank = !blank;
    }

  return 0;
}

int Ammo::getId()
{
  return 17;
}
