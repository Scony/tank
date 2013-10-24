#ifndef FREE_GAME_HPP
#define FREE_GAME_HPP

#include "Game.hpp"
#include "Spriter.hpp"
#include "Map.hpp"

class FreeGame : public Game
{
protected:
  Spriter * spriter;
  Map * map;
public:
  FreeGame(BITMAP * screen);
  ~FreeGame();

  void move();
  void draw();
};

#endif
