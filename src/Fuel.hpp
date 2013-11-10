#ifndef FUEL_HPP
#define FUEL_HPP

#include "Consumable.hpp"

class Fuel : public Consumable
{
  bool blank;
public:
  Fuel(Spriter * spriter, int amount);
  ~Fuel();

  int move();
  int getId();
};

#endif
