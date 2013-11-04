#ifndef TANK_HPP
#define TANK_HPP

#include <allegro.h>

#include "Spriter.hpp"
#include "Bullet.hpp"

class Tank
{
protected:
  Spriter * spriter;

  BITMAP * buffer;
public:
  Tank(Spriter * spriter);
  virtual ~Tank();

  virtual int move() = 0;
  virtual Bullet * breed();
  virtual int getRotation() = 0;
  BITMAP * getBuffer();
  int getSize();
};

#endif
