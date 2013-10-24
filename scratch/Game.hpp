#ifndef GAME_HPP
#define GAME_HPP

#include <allegro.h>

class Game
{
protected:
  BITMAP * buffer;
public:
  Game(int w, int h);
  ~Game();
  BITMAP * getBuffer();

  virtual void move() = 0;
};

#endif
