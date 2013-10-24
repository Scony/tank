#ifndef TEST_MAP_HPP
#define TEST_MAP_HPP

#include "Map.hpp"

class TestMap : public Map
{
public:
  TestMap(Spriter * spriter, int width, int height);
  ~TestMap();

  void move();
  Point getFocus();
};

#endif
