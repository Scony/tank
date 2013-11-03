#ifndef MAP_HPP
#define MAP_HPP

#include <allegro.h>

#include "Exception.hpp"
#include "Point.hpp"
#include "Spriter.hpp"

class Map
{
protected:
  Spriter * spriter;
  int width;
  int height;
  BITMAP * buffer;
public:
  Map(Spriter * spriter, int width, int height);
  Map();
  virtual ~Map();

  virtual void move() = 0;
  BITMAP * getBuffer();
  virtual Point getFocus() = 0;
};

#endif
