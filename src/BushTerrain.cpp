#include "BushTerrain.hpp"

BushTerrain::BushTerrain(Spriter * spriter) :
  Terrain(spriter)
{
  buffer = spriter->getTerrain(3);
}

BushTerrain::~BushTerrain()
{
}

int BushTerrain::getId()
{
  return 5;
}
