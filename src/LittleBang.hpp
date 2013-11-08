#ifndef LITTLE_BANG_HPP
#define LITTLE_BANG_HPP

#include "Bang.hpp"

class LittleBang : public Bang
{
  bool death;
  int latency;
public:
  LittleBang(Spriter * spriter);
  ~LittleBang();

  int move();
  int getId();

  bool isDeath();
};

#endif
