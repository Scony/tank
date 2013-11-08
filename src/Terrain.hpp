#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <allegro.h>

#include "Spriter.hpp"

class Terrain
{
protected:
  Spriter * spriter;
  BITMAP * buffer;
public:
  Terrain(Spriter * spriter);
  virtual ~Terrain();

  BITMAP * getBuffer();
  int getSize();
  virtual int getId();
};

#endif
