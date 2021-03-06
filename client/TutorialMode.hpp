#ifndef TUTORIAL_MODE_HPP
#define TUTORIAL_MODE_HPP

#include "Mode.hpp"
#include "Spriter.hpp"
#include "PolicyManager.hpp"
#include "Map.hpp"
#include "Tank.hpp"
#include "TankStatbar.hpp"

class TutorialMode : public Mode
{
protected:
  Spriter * spriter;
  PolicyManager * policy;
  Map * map;
  Tank * player1;
  TankStatbar * tsb;
public:
  TutorialMode(BITMAP * screen);
  ~TutorialMode();

  void move();
  void draw();
};

#endif
