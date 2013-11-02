#include "BrickTerrain.hpp"

BrickTerrain::BrickTerrain(Spriter * spriter) :
  Terrain(spriter)
{
  buffer = spriter->getTerrain(0);
}

BrickTerrain::~BrickTerrain()
{
}

bool BrickTerrain::isCollisionable()
{
  return true;
}

int BrickTerrain::getLevel()
{
  return 0;
}
