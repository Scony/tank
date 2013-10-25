#include "TutorialMap.hpp"

TutorialMap::TutorialMap(Spriter * spriter, int width, int height) :
  Map(spriter,width,height)
{
  clear_to_color(buffer,makecol(0,0,0));
  for(int i = 0; i < width; i++)
    for(int j = 0; j < height; j++)
      {
	blit(spriter->getTerrain(rand()%4),buffer,0,0,i*16,j*16,16,16);
      }
}

TutorialMap::~TutorialMap()
{
}

void TutorialMap::move()
{
  // clear_to_color(buffer,makecol(0,0,0));
  // for(int i = 0; i < width; i++)
  //   for(int j = 0; j < height; j++)
  //     {
  // 	blit(spriter->getTerrain(rand()%4),buffer,0,0,i*16,j*16,16,16);
  //     }
}

Point TutorialMap::getFocus()
{
  return Point(width*16/2,height*16/2);
}
