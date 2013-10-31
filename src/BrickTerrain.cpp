#include "BrickTerrain.hpp"

BrickTerrain::BrickTerrain(Spriter * spriter) :
  Terrain(spriter)
{
  buffer = spriter->getTerrain(0);
}

BrickTerrain::~BrickTerrain()
{
}

BITMAP * BrickTerrain::getBuffer()
{
  return buffer;
}

bool BrickTerrain::isCollisionable()
{
  return true;
}
