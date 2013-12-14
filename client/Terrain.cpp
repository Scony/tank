#include "Terrain.hpp"
#include "Configuration.hpp"

Terrain::Terrain(Spriter * spriter)
{
  this->spriter = spriter;
}

Terrain::~Terrain()
{
}

int Terrain::getSize()
{
  return Configuration::getInstance()->getMedium();
}

BITMAP * Terrain::getBuffer()
{
  return buffer;
}

int Terrain::getId()
{
  return 1;
}

int Terrain::getResistance()
{
  return 0;
}
