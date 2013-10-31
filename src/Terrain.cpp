#include "Terrain.hpp"

Terrain::Terrain(Spriter * spriter)
{
  this->spriter = spriter;
}

Terrain::~Terrain()
{
}

int Terrain::getSize()
{
  return spriter->getTerrainSize();
}
