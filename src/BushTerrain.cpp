#include "BushTerrain.hpp"

BushTerrain::BushTerrain(Spriter * spriter) :
  Terrain(spriter)
{
  buffer = spriter->getTerrain(3);
}

BushTerrain::~BushTerrain()
{
}

bool BushTerrain::isCollisionable()
{
  return false;
}
