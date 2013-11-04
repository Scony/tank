#include "PlayerTank.hpp"
#include "LineBullet.hpp"

PlayerTank::PlayerTank(Spriter * spriter) :
  Tank(spriter)
{
  buffer = spriter->getTank(0);
  offset = 0;
  rotation = 1;
  reload = 0;
  born = NULL;
}

PlayerTank::~PlayerTank()
{
}

int PlayerTank::move()
{
  offset = (offset + 1) % 2;
  reload = reload > 0 ? reload - 1 : 0;

  int intent = 0;

  if(key[KEY_UP])
    {
      buffer = spriter->getTank(0+offset);
      rotation = 1;
      intent = 1;
    }
  if(key[KEY_RIGHT])
    {
      buffer = spriter->getTank(2+offset);
      rotation = 2;
      intent = 2;
    }
  if(key[KEY_DOWN])
    {
      buffer = spriter->getTank(4+offset);
      rotation = 3;
      intent = 3;
    }
  if(key[KEY_LEFT])
    {
      buffer = spriter->getTank(6+offset);
      rotation = 4;
      intent = 4;
    }

  if(key[KEY_SPACE] && !reload)
    {
      born = new LineBullet(spriter,rotation);
      reload = 100;
    }

  return intent;
}

Bullet * PlayerTank::breed()
{
  if(born)
    {
      Bullet * tmp = born;
      born = NULL;
      return tmp;
    }

  return NULL;
}

int PlayerTank::getRotation()
{
  return rotation;
}
