#ifndef SPRITEER_HPP
#define SPRITEER_HPP

#include <allegro.h>
#include <iostream>

class Spriter
{
protected:
  BITMAP * sprite;
  BITMAP * terrain[5];
  BITMAP * tank[8];
  BITMAP * bang[3];
  BITMAP * bullet[4];
public:
  Spriter(std::string path);
  virtual ~Spriter();
  BITMAP * getSprite();
  virtual BITMAP * getTerrain(int index);
  virtual BITMAP * getTank(int index);
  virtual BITMAP * getBullet(int index);
  virtual int getTankSize();
  virtual int getTerrainSize();
};

#endif
