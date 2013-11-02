#ifndef BULLET_HPP
#define BULLET_HPP

#include <allegro.h>

#include "Spriter.hpp"

class Bullet
{
protected:
  Spriter * spriter;

  BITMAP * buffer;
public:
  Bullet(Spriter * spriter);
  virtual ~Bullet();

  virtual int move() = 0;
  BITMAP * getBuffer();
};

#endif
