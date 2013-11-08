#ifndef BANG_WRAPPER_HPP
#define BANG_WRAPPER_HPP

#include "Wrapper.hpp"
#include "Bang.hpp"

class BangWrapper : public Wrapper
{
  Bang * bng;
public:
  BangWrapper(int x, int y, int direction, Bang * bng);
  ~BangWrapper();

  int move();
  void bang();
  Wrapper * breed();

  Bang * getBang();
  BITMAP * getBuffer();
  int getSize();
  int getSpeed();
  int getId();
  int getResistance();
  int getPower();

  bool isVisible();
  bool isDeath();
  bool isBangMaker();
};

#endif
