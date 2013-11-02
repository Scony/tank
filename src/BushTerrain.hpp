#ifndef BUSH_TERRAIN_HPP
#define BUSH_TERRAIN_HPP

#include "Terrain.hpp"

class BushTerrain : public Terrain
{
public:
  BushTerrain(Spriter * spriter);
  ~BushTerrain();

  bool isCollisionable();
  int getLevel();
};

#endif
