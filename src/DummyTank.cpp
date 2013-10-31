#include "DummyTank.hpp"

DummyTank::DummyTank(Spriter * spriter, int speed) :
  Tank(spriter,speed)
{
  buffer = spriter->getTank(0);
}

DummyTank::~DummyTank()
{
}

int DummyTank::move()
{
  return 0;
}
