#ifndef CONSUMABLE_WRAPPER_HPP
#define CONSUMABLE_WRAPPER_HPP

#include "Wrapper.hpp"
#include "Consumable.hpp"

class ConsumableWrapper : public Wrapper
{
  Consumable * consumable;
public:
  ConsumableWrapper(int x, int y, int direction, Consumable * consumable);
  ~ConsumableWrapper();

  int move();
  void perform(int key, int value);
  Wrapper * breed();

  BITMAP * getBuffer();
  int getSize();
  int getSpeed();
  int getId();
  int getPower();

  bool isVisible();
  bool isDeath();
  bool isPerformer();
};

#endif
