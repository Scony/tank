#ifndef TUTORIAL_MAP_HPP
#define TUTORIAL_MAP_HPP

#include <list>

#include "Map.hpp"
#include "Terrain.hpp"
#include "Tank.hpp"

struct TankBox
{
  int x;
  int y;
  int dir;
  Tank * tank;
  TankBox(int x, int y, Tank * tank, int dir)
  {
    this->x = x;
    this->y = y;
    this->dir = dir;
    this->tank = tank;
  }
};

class TutorialMap : public Map
{
  Terrain *** terrains;
  std::list<TankBox> tanks;
public:
  TutorialMap(Spriter * spriter, int width, int height);
  ~TutorialMap();

  void move();
  Point getFocus();
};

#endif
