#ifndef TUTORIAL_GAME_HPP
#define TUTORIAL_GAME_HPP

#include "Game.hpp"
#include "Spriter.hpp"
#include "PolicyManager.hpp"
#include "Map.hpp"

class TutorialGame : public Game
{
protected:
  Spriter * spriter;
  PolicyManager * policy;
  Map * map;
public:
  TutorialGame(BITMAP * screen);
  ~TutorialGame();

  void move();
  void draw();
};

#endif
