#ifndef TEST_HPP
#define TEST_HPP

#include "Game.hpp"
#include "Loader.hpp"

class Test : public Game
{
  Loader ld;
public:
  Test(int w, int h);
  ~Test();

  void move();
};

#endif
