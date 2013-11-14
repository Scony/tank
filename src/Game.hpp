#ifndef GAME_HPP
#define GAME_HPP

#include <allegro.h>

#include "Mode.hpp"
#include "Menu.hpp"

class Game
{
  BITMAP * screen;
  Mode * mode;
  Menu * menu;

  bool menuOn;
  bool done;
  bool escPressed;
public:
  Game(BITMAP * screen);
  ~Game();

  void move();
  void draw();

  bool isDone();
};

#endif
