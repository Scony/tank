#include "ConcreteTerrain.hpp"

ConcreteTerrain::ConcreteTerrain(Spriter * spriter) :
  Terrain(spriter)
{
  buffer = spriter->getTerrain(1);
}

ConcreteTerrain::~ConcreteTerrain()
{
}

bool ConcreteTerrain::isCollisionable()
{
  return true;
}

int ConcreteTerrain::getLevel()
{
  return 0;
}
