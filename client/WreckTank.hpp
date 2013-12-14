#ifndef WRECK_TANK_HPP
#define WRECK_TANK_HPP

#include "Tank.hpp"

class WreckTank : public Tank
{
  bool consumed;
public:
  WreckTank(Spriter * spriter);
  ~WreckTank();

  int move();
  int getId();
};

#endif
