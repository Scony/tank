#ifndef BRICK_TERRAIN_HPP
#define BRICK_TERRAIN_HPP

#include "Terrain.hpp"

class BrickTerrain : public Terrain
{
  BITMAP * buffer;
public:
  BrickTerrain(Spriter * spriter);
  ~BrickTerrain();

  BITMAP * getBuffer();
};

#endif
