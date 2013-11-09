#ifndef TUTORIAL_GAME_HPP
#define TUTORIAL_GAME_HPP

#include "Game.hpp"
#include "Spriter.hpp"
#include "PolicyManager.hpp"
#include "Map.hpp"
#include "Tank.hpp"

class TutorialGame : public Game
{
protected:
  Spriter * spriter;
  PolicyManager * policy;
  Map * map;
  Tank * player1;
public:
  TutorialGame(BITMAP * screen);
  ~TutorialGame();

  void move();
  void draw();
};

#endif
