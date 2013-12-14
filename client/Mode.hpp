#ifndef MODE_HPP
#define MODE_HPP

#include <allegro.h>

class Mode
{
protected:
  BITMAP * screen;
public:
  Mode(BITMAP * screen);
  virtual ~Mode();

  virtual void move() = 0;
  virtual void draw() = 0;
};

#endif
