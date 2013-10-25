#ifndef TUTORIAL_MAP_HPP
#define TUTORIAL_MAP_HPP

#include "Map.hpp"

class TutorialMap : public Map
{
public:
  TutorialMap(Spriter * spriter, int width, int height);
  ~TutorialMap();

  void move();
  Point getFocus();
};

#endif
