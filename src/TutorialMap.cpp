#include <math.h>

#include "TutorialMap.hpp"
#include "BrickTerrain.hpp"
#include "DummyTank.hpp"
#include "PlayerTank.hpp"
#include "AITank.hpp"

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
  tanks.push_back(TankBox(0,0,new DummyTank(spriter),1));
  tanks.push_back(TankBox(0,32,new PlayerTank(spriter),1));
  // tanks.push_back(TankBox(0,64,new PlayerTank(spriter),1));
  tanks.push_back(TankBox(0,96,new AITank(spriter),1));
  tanks.push_back(TankBox(0,128,new AITank(spriter),1));

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
  // clear tanks
  for(list<TankBox>::iterator i = tanks.begin(); i != tanks.end(); i++)
    rectfill(buffer,i->x,i->y,i->x+31,i->y+31,makecol(0,0,0));

  // handle tank intents + collisions
  for(list<TankBox>::iterator i = tanks.begin(); i != tanks.end(); i++)
    {
      int x = i->x;
      int y = i->y;

      int intent = i->tank->move();
      if(intent == 0 || i->dir == intent)
	switch(intent)
	  {
	  case 1:
	    y--;
	    break;
	  case 2:
	    x++;
	    break;
	  case 3:
	    y++;
	    break;
	  case 4:
	    x--;
	    break;
	  }
      else
	{
	  x = round((double)x / 16) * 16;
	  y = round((double)y / 16) * 16;
	}

      if(intent)
	i->dir = intent;
      
      // map bounds
      if(x < 0 || x + 32 > width * 16 || y < 0 || y + 32 > height * 16)
	continue;

      // terrain collisions
      int ix = x / 16;
      int iy = y / 16;
      int ixx = (x + 31) / 16;
      int iyy = (y + 31) / 16;
      bool collision = false;
      for(int j = ix; j <= ixx && !collision; j++)
	for(int k = iy; k <= iyy && !collision; k++)
	  if(terrains[j][k] != NULL && terrains[j][k]->isCollisionable())
	    collision = true;
      if(collision)
	continue;

      // success
      i->x = x;
      i->y = y;
    }

  // redraw
  // clear_to_color(buffer,makecol(0,0,0));
  for(list<TankBox>::iterator i = tanks.begin(); i != tanks.end(); i++)
    blit(i->tank->getBuffer(),buffer,0,0,i->x,i->y,32,32);
  // for(int i = 0; i < width; i++)
  //   for(int j = 0; j < height; j++)
  //     {
  // 	if(terrains[i][j])
  // 	  blit(terrains[i][j]->getBuffer(),buffer,0,0,i*16,j*16,16,16);
  //     }
}

Point TutorialMap::getFocus()
{
  return Point(width*16/2,height*16/2);
}
