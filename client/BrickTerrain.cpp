#include "BrickTerrain.hpp"

BrickTerrain::BrickTerrain(Spriter * spriter) :
  Terrain(spriter)
{
  buffer = spriter->getTerrain(0);
}

BrickTerrain::~BrickTerrain()
{
}

int BrickTerrain::getId()
{
  return 2;
}
