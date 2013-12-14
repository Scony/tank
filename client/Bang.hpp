#ifndef BANG_HPP
#define BANG_HPP

#include <allegro.h>

#include "Spriter.hpp"

class Bang
{
protected:
  Spriter * spriter;
  BITMAP * buffer;
public:
  Bang(Spriter * spriter);
  virtual ~Bang();

  virtual bool isDeath() = 0;

  virtual int move() = 0;

  BITMAP * getBuffer();
  virtual int getId();
};

#endif
