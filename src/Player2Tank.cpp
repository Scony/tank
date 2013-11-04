#include "Player2Tank.hpp"

Player2Tank::Player2Tank(Spriter * spriter) :
  Tank(spriter)
{
  buffer = spriter->getTank(0);
  offset = 0;
  rotation = 1;
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
      rotation = 1;
      return 1;
    }
  if(key[KEY_D])
    {
      buffer = spriter->getTank(2+offset);
      rotation = 2;
      return 2;
    }
  if(key[KEY_S])
    {
      buffer = spriter->getTank(4+offset);
      rotation = 3;
      return 3;
    }
  if(key[KEY_A])
    {
      buffer = spriter->getTank(6+offset);
      rotation = 4;
      return 4;
    }

  return 0;
}

int Player2Tank::getRotation()
{
  return rotation;
}
