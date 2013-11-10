#ifndef SPRITEER_HPP
#define SPRITEER_HPP

#include <allegro.h>
#include <iostream>

class Spriter
{
protected:
  BITMAP * sprite;
  BITMAP * terrain[5];
  BITMAP * tank[3][8];
  BITMAP * bang[3];
  BITMAP * bullet[4];
  BITMAP * consumable[2];
  BITMAP * wreck;
public:
  Spriter(std::string path);
  virtual ~Spriter();
  BITMAP * getSprite();
  virtual BITMAP * getTerrain(int index);
  virtual BITMAP * getTank(int kind, int index);
  virtual BITMAP * getBullet(int index);
  virtual BITMAP * getBang(int index);
  virtual BITMAP * getWreck();
  virtual int getTankSize();
  virtual int getTerrainSize();
  virtual int getBangSize();
};

#endif
