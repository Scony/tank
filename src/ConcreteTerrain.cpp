#include "ConcreteTerrain.hpp"

ConcreteTerrain::ConcreteTerrain(Spriter * spriter) :
  Terrain(spriter)
{
  buffer = spriter->getTerrain(1);
}

ConcreteTerrain::~ConcreteTerrain()
{
}

int ConcreteTerrain::getId()
{
  return 3;
}

int ConcreteTerrain::getResistance()
{
  return 1;
}
