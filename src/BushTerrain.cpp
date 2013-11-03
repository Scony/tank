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

int BushTerrain::getLevel()
{
  return 1;
}

bool BushTerrain::isSpawnable()
{
  return true;
}
