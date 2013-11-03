#ifndef TUTORIAL_MAP_HPP
#define TUTORIAL_MAP_HPP

#include <list>
#include <iostream>

#include "Map.hpp"
#include "Terrain.hpp"
#include "Tank.hpp"
#include "WrapperBox.hpp"

class TutorialMap : public Map
{
  Terrain *** terrains;
  std::list<WrapperBox> objects;
public:
  TutorialMap(Spriter * spriter, std::string fileName);
  ~TutorialMap();

  void move();
  Point getFocus();
  void addTank(Tank * tank);
};

#endif
