#ifndef CONSUMABLE_HPP
#define CONSUMABLE_HPP

#include <allegro.h>

#include "Spriter.hpp"

class Consumable
{
protected:
  Spriter * spriter;
  BITMAP * buffer;

  int amount;
  int blink;
  int blinkMax;

  void update();
public:
  Consumable(Spriter * spriter, int amount);
  virtual ~Consumable();

  bool isDeath();

  virtual int move() = 0;
  int consume();

  virtual int getId();
  BITMAP * getBuffer();
};

#endif
