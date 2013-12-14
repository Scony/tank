#ifndef TUTORIAL_MAP_HPP
#define TUTORIAL_MAP_HPP

#include <list>
#include <iostream>

#include "Map.hpp"
#include "PolicyManager.hpp"
#include "Terrain.hpp"
#include "Tank.hpp"
#include "WrapperBox.hpp"

class TutorialMap : public Map
{
  PolicyManager * policy;
  Terrain *** terrains;
  std::list<Point> spots;
  std::list<WrapperBox> objects;

  bool detectRectsCollision(int x11, int y11, int x12, int y12,
			    int x21, int y21, int x22, int y22);
public:
  TutorialMap(Spriter * spriter, PolicyManager * policy, std::string fileName);
  ~TutorialMap();

  void addTank(Tank * tank);

  void move();

  Point getFocus();
};

#endif
