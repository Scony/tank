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
  tanks.push_back(TankBox(0,0,1,new DummyTank(spriter)));
  tanks.push_back(TankBox(0,32,1,new PlayerTank(spriter)));
  // tanks.push_back(TankBox(0,64,1,new PlayerTank(spriter)));
  tanks.push_back(TankBox(0,96,1,new AITank(spriter)));
  tanks.push_back(TankBox(0,128,1,new AITank(spriter)));

  // initial draw
  clear_to_color(buffer,makecol(0,0,0));
  for(list<TankBox>::iterator it = tanks.begin(); it != tanks.end(); it++)
    blit(it->getTank()->getBuffer(),buffer,0,0,it->getX(),it->getY(),32,32);
  for(int i = 0; i < width; i++)
    for(int j = 0; j < height; j++)
      {
	if(terrains[i][j])
	  blit(terrains[i][j]->getBuffer(),buffer,0,0,i*16,j*16,16,16);
      }
}

TutorialMap::~TutorialMap()
{
  for(list<TankBox>::iterator it = tanks.begin(); it != tanks.end(); it++)
    delete it->getTank();

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
  for(list<TankBox>::iterator it = tanks.begin(); it != tanks.end(); it++)
    rectfill(buffer,it->getX(),it->getY(),it->getX()+31,it->getY()+31,makecol(0,0,0));

  // handle tank intents + terrain collisions
  for(list<TankBox>::iterator it = tanks.begin(); it != tanks.end(); it++)
    {
      int intent = it->getTank()->move();
      if(intent == 0 || it->getDirection() == intent)
	switch(intent)
	  {
	  case 1:
	    it->setNewY(it->getY()-1);
	    break;
	  case 2:
	    it->setNewX(it->getX()+1);
	    break;
	  case 3:
	    it->setNewY(it->getY()+1);
	    break;
	  case 4:
	    it->setNewX(it->getX()-1);
	  }
      else
	{
	  it->setNewX(round((double)it->getX() / 16) * 16);
	  it->setNewY(round((double)it->getY() / 16) * 16);
	}

      if(intent)
	it->setNewDirection(intent);
      
      // map bounds
      if(it->getNewX() < 0 || it->getNewX() + 32 > width * 16 || it->getNewY() < 0 || it->getNewY() + 32 > height * 16)
	{
	  it->resetChanges();
	  continue;
	}

      // terrain collisions
      int ix = it->getNewX() / 16;
      int iy = it->getNewY() / 16;
      int ixx = (it->getNewX() + 31) / 16;
      int iyy = (it->getNewY() + 31) / 16;
      bool collision = false;
      for(int i = ix; i <= ixx && !collision; i++)
	for(int j = iy; j <= iyy && !collision; j++)
	  if(terrains[i][j] != NULL && terrains[i][j]->isCollisionable())
	    collision = true;
      if(collision)
	{
	  it->resetChanges();
	  continue;
	}
    }

  // handle tank vs tank collisions
  for(list<TankBox>::iterator it = tanks.begin(); it != tanks.end(); it++)
    for(list<TankBox>::iterator itt = tanks.begin(); itt != tanks.end(); itt++)
      {
	if(it != itt)
	  {
	    int x11 = it->getNewX();
	    int y11 = it->getNewY();
	    int x12 = it->getNewX() + 31;
	    int y12 = it->getNewY() + 31;

	    int x21 = itt->getNewX();
	    int y21 = itt->getNewY();
	    int x22 = itt->getNewX() + 31;
	    int y22 = itt->getNewY() + 31;

	    if((x11 <= x21 && x21 <= x12 && y11 <= y21 && y21 <= y12) ||
	       (x11 <= x21 && x21 <= x12 && y11 <= y22 && y22 <= y12) ||
	       (x11 <= x22 && x22 <= x12 && y11 <= y22 && y22 <= y12) ||
	       (x11 <= x22 && x22 <= x12 && y11 <= y21 && y21 <= y12))
	      {
		it->resetChanges();
		itt->resetChanges();
	      }
	  }
      }

  // apply changes
  for(list<TankBox>::iterator it = tanks.begin(); it != tanks.end(); it++)
    it->applyChanges();

  // redraw
  // clear_to_color(buffer,makecol(0,0,0));
  for(list<TankBox>::iterator it = tanks.begin(); it != tanks.end(); it++)
    blit(it->getTank()->getBuffer(),buffer,0,0,it->getX(),it->getY(),32,32);
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
