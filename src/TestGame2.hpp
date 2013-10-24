#ifndef TEST_GAME_2_HPP
#define TEST_GAME_2_HPP

#include "Game.hpp"
#include "Spriter.hpp"
#include "Map.hpp"

class TestGame2 : public Game
{
protected:
  Spriter * spriter;
  Map * map;
public:
  TestGame2(BITMAP * screen);
  ~TestGame2();

  void move();
  void draw();
};

#endif
