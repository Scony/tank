#include "AITank.hpp"

AITank::AITank(Spriter * spriter, int speed) :
  Tank(spriter,speed)
{
  buffer = spriter->getTank(0);
  offset = 0;
  intent = 0;
  length = 0;
}

AITank::~AITank()
{
}

int AITank::move()
{
  offset = (offset + 1) % 2;
  if(length-- == 0)
    {
      intent = rand() % 5;
      length = rand() % 50;
    }

  switch(intent)
    {
    case 1:
      buffer = spriter->getTank(0+offset);
      return 1;
    case 2:
      buffer = spriter->getTank(2+offset);
      return 2;
    case 3:
      buffer = spriter->getTank(4+offset);
      return 3;
    case 4:
      buffer = spriter->getTank(6+offset);
      return 4;
    }

  return 0;
}
