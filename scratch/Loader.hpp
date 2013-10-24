#ifndef LOADER_HPP
#define LOADER_HPP

#include <allegro.h>

class Loader
{
  BITMAP * sprite;
  BITMAP * terrain[4];
  BITMAP * tank[8];
  BITMAP * bang[3];
  BITMAP * bullet[4];
public:
  Loader();
  ~Loader();
  BITMAP * getSprite();
  BITMAP * getTerrain(int index);
};

#endif
