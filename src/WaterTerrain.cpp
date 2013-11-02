#include "WaterTerrain.hpp"

WaterTerrain::WaterTerrain(Spriter * spriter) :
  Terrain(spriter)
{
  buffer = spriter->getTerrain(4);
}

WaterTerrain::~WaterTerrain()
{
}

bool WaterTerrain::isCollisionable()
{
  return true;
}

int WaterTerrain::getLevel()
{
  return -1;
}
