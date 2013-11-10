#include "WreckTank.hpp"

WreckTank::WreckTank(Spriter * spriter) :
  Tank(spriter)
{
  buffer = spriter->getWreck();
}

WreckTank::~WreckTank()
{
}

int WreckTank::move()
{
  return 0;
}

int WreckTank::getId()
{
  return 15;
}
