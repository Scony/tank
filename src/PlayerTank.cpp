#include "PlayerTank.hpp"

PlayerTank::PlayerTank(Spriter * spriter, int speed) :
  Tank(spriter,speed)
{
  buffer = spriter->getTank(0);
  offset = 0;
}

PlayerTank::~PlayerTank()
{
}

int PlayerTank::move()
{
  offset = (offset + 1) % 2;

  if(key[KEY_UP])
    {
      buffer = spriter->getTank(0+offset);
      return 1;
    }
  if(key[KEY_RIGHT])
    {
      buffer = spriter->getTank(2+offset);
      return 2;
    }
  if(key[KEY_DOWN])
    {
      buffer = spriter->getTank(4+offset);
      return 3;
    }
  if(key[KEY_LEFT])
    {
      buffer = spriter->getTank(6+offset);
      return 4;
    }

  return 0;
}
