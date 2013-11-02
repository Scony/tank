#include "PavementTerrain.hpp"

PavementTerrain::PavementTerrain(Spriter * spriter) :
  Terrain(spriter)
{
  buffer = spriter->getTerrain(2);
}

PavementTerrain::~PavementTerrain()
{
}

bool PavementTerrain::isCollisionable()
{
  return false;
}

int PavementTerrain::getLevel()
{
  return -1;
}
