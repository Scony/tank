#include "DummyTank.hpp"

DummyTank::DummyTank(Spriter * spriter) :
  Tank(spriter)
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
