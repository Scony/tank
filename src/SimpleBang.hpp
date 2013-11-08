#ifndef SIMPLE_BANG_HPP
#define SIMPLE_BANG_HPP

#include "Bang.hpp"

class SimpleBang : public Bang
{
  bool death;
  int stance;
public:
  SimpleBang(Spriter * spriter);
  ~SimpleBang();

  int move();
  int getId();

  bool isDeath();
};

#endif
