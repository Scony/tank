#include "Player2Tank.hpp"

Player2Tank::Player2Tank(Spriter * spriter) :
  Tank(spriter)
{
  buffer = spriter->getTank(1,0);
}

Player2Tank::Player2Tank(Spriter * spriter, int rotation,
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
  buffer = spriter->getTank(1,0);
}

Player2Tank::~Player2Tank()
{
}

int Player2Tank::move()
{
  update();

  int intent = 0;
  
  if(!isLocked())
    {
      if(key[KEY_W])
	{
	  buffer = spriter->getTank(1,0+offset);
	  rotation = 1;
	  intent = 1;
	}
      if(key[KEY_D])
	{
	  buffer = spriter->getTank(1,2+offset);
	  rotation = 2;
	  intent = 2;
	}
      if(key[KEY_S])
	{
	  buffer = spriter->getTank(1,4+offset);
	  rotation = 3;
	  intent = 3;
	}
      if(key[KEY_A])
	{
	  buffer = spriter->getTank(1,6+offset);
	  rotation = 4;
	  intent = 4;
	}
    }

  if(key[KEY_ENTER])
    shoot();

  return intent;
}
