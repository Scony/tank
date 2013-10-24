#include "TestMap.hpp"

TestMap::TestMap(Spriter * spriter, int width, int height) :
  Map(spriter,width,height)
{
}

TestMap::~TestMap()
{
}

void TestMap::move()
{
  while(!key[KEY_ESC]);
  clear_to_color(buffer,makecol(0,0,0));
  for(int i = 0; i < width; i++)
    for(int j = 0; j < height; j++)
      {
	blit(spriter->getTerrain(rand()%4),buffer,0,0,i*16,j*16,16,16);
      }
}

Point TestMap::getFocus()
{
  return Point(-1,-1);
}
