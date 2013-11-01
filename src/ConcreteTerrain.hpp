#ifndef CONCRETE_TERRAIN_HPP
#define CONCRETE_TERRAIN_HPP

#include "Terrain.hpp"

class ConcreteTerrain : public Terrain
{
public:
  ConcreteTerrain(Spriter * spriter);
  ~ConcreteTerrain();

  bool isCollisionable();
};

#endif
