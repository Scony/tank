#ifndef TUTORIAL_MAP_HPP
#define TUTORIAL_MAP_HPP

#include <list>

#include "Map.hpp"
#include "Terrain.hpp"
#include "Tank.hpp"

class TutorialMap : public Map
{
  Terrain *** terrains;
  // std::List<Tank*> tanks;	// pointer copying may cause problem
public:
  TutorialMap(Spriter * spriter, int width, int height);
  ~TutorialMap();

  void move();
  Point getFocus();
};

#endif
