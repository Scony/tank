#include "WreckTank.hpp"

WreckTank::WreckTank(Spriter * spriter) :
  Tank(spriter)
{
  buffer = spriter->getWreck();
  burn = true;
  consumed = false;
}

WreckTank::~WreckTank()
{
}

int WreckTank::move()
{
  if(consumed)
    burn = false;
  consumed = true;
  return 0;
}

int WreckTank::getId()
{
  return 15;
}
