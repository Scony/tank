#ifndef PAVEMENT_TERRAIN_HPP
#define PAVEMENT_TERRAIN_HPP

#include "Terrain.hpp"

class PavementTerrain : public Terrain
{
public:
  PavementTerrain(Spriter * spriter);
  ~PavementTerrain();

  bool isCollisionable();
  int getLevel();
  bool isSpawnable();
};

#endif
