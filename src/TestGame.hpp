#ifndef TEST_GAME_HPP
#define TEST_GAME_HPP

#include "Game.hpp"
#include "Spriter.hpp"

class TestGame : public Game
{
  Spriter * sp;
  BITMAP * buffer;
public:
  TestGame(BITMAP * screen);
  ~TestGame();

  void move();
  void draw();
};

#endif
