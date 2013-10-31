#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <allegro.h>

#include "Spriter.hpp"

class Terrain
{
protected:
  Spriter * spriter;
public:
  Terrain(Spriter * spriter);
  virtual ~Terrain();

  virtual BITMAP * getBuffer() = 0;
  int getSize();
  virtual bool isCollisionable() = 0;
};

#endif
