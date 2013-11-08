#include "PavementTerrain.hpp"

PavementTerrain::PavementTerrain(Spriter * spriter) :
  Terrain(spriter)
{
  buffer = spriter->getTerrain(2);
}

PavementTerrain::~PavementTerrain()
{
}

int PavementTerrain::getId()
{
  return 4;
}
