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

  virtual bool isDeath() = 0;

  virtual int move() = 0;

  BITMAP * getBuffer();
  Spriter * getSpriter();

  virtual int getId();
  virtual int getPower() = 0;
};

#endif
