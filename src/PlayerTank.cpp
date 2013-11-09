#include "PlayerTank.hpp"

PlayerTank::PlayerTank(Spriter * spriter) :
  Tank(spriter)
{
  buffer = spriter->getTank(0);
}

PlayerTank::PlayerTank(Spriter * spriter, int rotation,
		       int hp, int hpMax,
		       int ammo, int ammoMax,
		       int fuel, int fuelMax,
		       int reload, int reloadMax) :
  Tank(spriter,rotation,
       hp,hpMax,
       ammo,ammoMax,
       fuel,fuelMax,
       reload,reloadMax)
{
  buffer = spriter->getTank(0);
}

PlayerTank::~PlayerTank()
{
}

int PlayerTank::move()
{
  update();

  int intent = 0;

  if(!isLocked())
    {
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
    }

  if(key[KEY_ENTER])
    shoot();

  return intent;
}

int PlayerTank::getId()
{
  return 8;
}
