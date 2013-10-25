#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <allegro.h>

#include "Spriter.hpp"

class Terrain
{
  Spriter * spriter;
public:
  Terrain(Spriter * spriter);
  ~Terrain();

  virtual BITMAP * getBuffer() = 0;
};

#endif
