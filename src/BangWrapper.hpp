#ifndef BANG_WRAPPER_HPP
#define BANG_WRAPPER_HPP

#include "Wrapper.hpp"
#include "Bang.hpp"

class BangWrapper : public Wrapper
{
  Bang * bang;
public:
  BangWrapper(int x, int y, int direction, Bang * bang);
  ~BangWrapper();

  int move();
  void perform(int key, int value);
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
  bool isPerformer();
};

#endif
