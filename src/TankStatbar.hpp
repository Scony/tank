#ifndef TANK_STATBAR_HPP
#define TANK_STATBAR_HPP

#include <allegro.h>

#include "Tank.hpp"

class TankStatbar
{
  BITMAP * buffer;

  Tank * tank;
public:
  TankStatbar(Tank * tank, int width, int height);
  ~TankStatbar();

  void move();

  BITMAP * getBuffer();
};

#endif
