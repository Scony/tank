#ifndef GAME_HPP
#define GAME_HPP

#include <allegro.h>

class Game
{
protected:
  BITMAP * screen;
public:
  Game(BITMAP * screen);
  virtual ~Game();

  virtual void move() = 0;
  virtual void draw() = 0;
};

#endif
