#include "TutorialMap.hpp"
#include "BrickTerrain.hpp"
#include "DummyTank.hpp"
#include "PlayerTank.hpp"

using namespace std;

TutorialMap::TutorialMap(Spriter * spriter, int width, int height) :
  Map(spriter,width,height)
{
  // terrains init
  terrains = new Terrain ** [width];
  for(int i = 0; i < width; i++)
    terrains[i] = new Terrain * [height];
  for(int i = 0; i < width; i++)
    for(int j = 0; j < height; j++)
      if(rand()%100 > 96)
	terrains[i][j] = new BrickTerrain(spriter);
      else
	terrains[i][j] = NULL;

  // tanks init
  tanks.push_back(TankBox(10,10,new DummyTank(spriter,1)));
  tanks.push_back(TankBox(10,42,new PlayerTank(spriter,1)));
  tanks.push_back(TankBox(10,74,new PlayerTank(spriter,3)));

  // initial draw
  clear_to_color(buffer,makecol(0,0,0));
  for(list<TankBox>::iterator i = tanks.begin(); i != tanks.end(); i++)
    blit(i->tank->getBuffer(),buffer,0,0,i->x,i->y,32,32);
  for(int i = 0; i < width; i++)
    for(int j = 0; j < height; j++)
      {
	if(terrains[i][j])
	  blit(terrains[i][j]->getBuffer(),buffer,0,0,i*16,j*16,16,16);
      }
}

TutorialMap::~TutorialMap()
{
  for(list<TankBox>::iterator i = tanks.begin(); i != tanks.end(); i++)
    delete i->tank;

  for(int i = 0; i < width; i++)
    for(int j = 0; j < height; j++)
      if(terrains[i][j])
	delete terrains[i][j];
  
  for(int i = 0; i < width; i++)
    delete [] terrains[i];

  delete [] terrains;

}

void TutorialMap::move()
{
  // handle tank intents
  for(list<TankBox>::iterator i = tanks.begin(); i != tanks.end(); i++)
    {
      switch(i->tank->move())
	{
	case 1:
	  i->y -= i->tank->getSpeed();
	  break;
	case 2:
	  i->x += i->tank->getSpeed();
	  break;
	case 3:
	  i->y += i->tank->getSpeed();
	  break;
	case 4:
	  i->x -= i->tank->getSpeed();
	  break;
	}
    }

  // redraw
  clear_to_color(buffer,makecol(0,0,0));
  for(list<TankBox>::iterator i = tanks.begin(); i != tanks.end(); i++)
    blit(i->tank->getBuffer(),buffer,0,0,i->x,i->y,32,32);
  for(int i = 0; i < width; i++)
    for(int j = 0; j < height; j++)
      {
  	if(terrains[i][j])
  	  blit(terrains[i][j]->getBuffer(),buffer,0,0,i*16,j*16,16,16);
      }
}

Point TutorialMap::getFocus()
{
  return Point(width*16/2,height*16/2);
}
