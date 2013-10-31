#ifndef TANK_HPP
#define TANK_HPP

#include <allegro.h>

#include "Spriter.hpp"

class Tank
{
protected:
  Spriter * spriter;

  BITMAP * buffer;
  int speed;
public:
  Tank(Spriter * spriter, int speed);
  virtual ~Tank();

  virtual int move() = 0;
  BITMAP * getBuffer();
  int getSpeed();
};

#endif
