#include "WaterTerrain.hpp"

WaterTerrain::WaterTerrain(Spriter * spriter) :
  Terrain(spriter)
{
  buffer = spriter->getTerrain(4);
}

WaterTerrain::~WaterTerrain()
{
}

int WaterTerrain::getId()
{
  return 6;
}
