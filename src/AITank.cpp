#include "AITank.hpp"

AITank::AITank(Spriter * spriter) :
  Tank(spriter)
{
  buffer = spriter->getTank(2,0);

  intent = 0;
  length = 0;
}

AITank::AITank(Spriter * spriter, int rotation,
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
  buffer = spriter->getTank(2,0);

  intent = 0;
  length = 0;
}

AITank::~AITank()
{
}

int AITank::move()
{
  update();

  if(!isLocked() && !length--)
    {
      intent = rand() % 5;
      length = rand() % 70;
    }


  if(!isLocked())
    {
      switch(intent)
	{
	case 1:
	  buffer = spriter->getTank(2,0+offset);
	  rotation = 1;
	  break;
	case 2:
	  buffer = spriter->getTank(2,2+offset);
	  rotation = 2;
	  break;
	case 3:
	  buffer = spriter->getTank(2,4+offset);
	  rotation = 3;
	  break;
	case 4:
	  buffer = spriter->getTank(2,6+offset);
	  rotation = 4;
	}
    }

  if(rand() % 100 > 97)
    shoot();

  if(isLocked())
    return 0;

  return intent;
}

int AITank::getId()
{
  return 14;
}
