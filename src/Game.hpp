#ifndef GAME_HPP
#define GAME_HPP

#include <allegro.h>

#include "Mode.hpp"

class Game
{
  BITMAP * screen;
  Mode * mode;

  bool menu;
  bool flag;
public:
  Game(BITMAP * screen);
  ~Game();

  void move();
  void draw();
};

#endif
