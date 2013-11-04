#include "Player2Tank.hpp"

Player2Tank::Player2Tank(Spriter * spriter) :
  Tank(spriter)
{
  buffer = spriter->getTank(0);
  offset = 0;
}

Player2Tank::~Player2Tank()
{
}

int Player2Tank::move()
{
  offset = (offset + 1) % 2;

  if(key[KEY_W])
    {
      buffer = spriter->getTank(0+offset);
      return 1;
    }
  if(key[KEY_D])
    {
      buffer = spriter->getTank(2+offset);
      return 2;
    }
  if(key[KEY_S])
    {
      buffer = spriter->getTank(4+offset);
      return 3;
    }
  if(key[KEY_A])
    {
      buffer = spriter->getTank(6+offset);
      return 4;
    }

  return 0;
}
