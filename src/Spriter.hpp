#ifndef SPRITEER_HPP
#define SPRITEER_HPP

#include <allegro.h>
#include <iostream>

class Spriter
{
  BITMAP * sprite;
  BITMAP * terrain[4];
  BITMAP * tank[8];
  BITMAP * bang[3];
  BITMAP * bullet[4];
public:
  Spriter(std::string path);
  ~Spriter();
  BITMAP * getSprite();
  BITMAP * getTerrain(int index);
  BITMAP * getTank(int index);
};

#endif
