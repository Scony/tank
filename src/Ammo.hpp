#ifndef AMMO_HPP
#define AMMO_HPP

#include "Consumable.hpp"

class Ammo : public Consumable
{
  bool blank;
public:
  Ammo(Spriter * spriter, int amount);
  ~Ammo();

  int move();
  int getId();
};

#endif
