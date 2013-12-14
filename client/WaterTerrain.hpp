#ifndef WATER_TERRAIN_HPP
#define WATER_TERRAIN_HPP

#include "Terrain.hpp"

class WaterTerrain : public Terrain
{
public:
  WaterTerrain(Spriter * spriter);
  ~WaterTerrain();

  int getId();
};

#endif
