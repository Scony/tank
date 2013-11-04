#include <fstream>
#include <math.h>

#include "TutorialMap.hpp"
#include "BrickTerrain.hpp"
#include "ConcreteTerrain.hpp"
#include "PavementTerrain.hpp"
#include "BushTerrain.hpp"
#include "WaterTerrain.hpp"
#include "TankWrapper.hpp"
#include "BulletWrapper.hpp"
#include "LineBullet.hpp"

using namespace std;

TutorialMap::TutorialMap(Spriter * spriter, string fileName)
{
  this->spriter = spriter;

  ifstream in(fileName.c_str());
  if(!in)
    throw new Exception("Can not load " + fileName);

  in >> width;
  in >> height;

  buffer = create_bitmap(width*16,height*16); // HARDCODE ! todo
  if(!buffer)
    throw new Exception("Can not create bitmap");

  // terrains init
  terrains = new Terrain ** [width];
  for(int i = 0; i < width; i++)
    terrains[i] = new Terrain * [height];
  for(int j = 0; j < height; j++)
    for(int i = 0; i < width; i++)
      {
	int kind;
	in >> kind;
	switch(kind)
	  {
	  default:
	    terrains[i][j] = NULL;
	    break;
	  case 1:
	    terrains[i][j] = new BrickTerrain(spriter);
	    break;
	  case 2:
	    terrains[i][j] = new ConcreteTerrain(spriter);
	    break;
	  case 3:
	    terrains[i][j] = new PavementTerrain(spriter);
	    break;
	  case 4:
	    terrains[i][j] = new BushTerrain(spriter);
	    break;
	  case 5:
	    terrains[i][j] = new WaterTerrain(spriter);
	    break;
	  }
      }

  in.close();

  objects.push_back(WrapperBox(new BulletWrapper(0,0,2,new LineBullet(spriter,2)))); // tmp todo: rm

  // initial draw
  clear_to_color(buffer,makecol(0,0,0));
  for(int i = 0; i < width; i++)
    for(int j = 0; j < height; j++)
      {
	if(terrains[i][j])
	  masked_blit(terrains[i][j]->getBuffer(),buffer,0,0,i*16,j*16,16,16);
      }
}

TutorialMap::~TutorialMap()
{
  // for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
  //   it->getWrapper()->deleteWrappee();
  // todo TankWrapper cares tank dth

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
  // clear objects
  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
    {
      Wrapper * pw = it->getWrapper();

      if(!pw->isClerable())
	continue;

      rectfill(buffer,
	       pw->getX(),
	       pw->getY(),
	       pw->getX() + pw->getSize() - 1,
	       pw->getY() + pw->getSize() - 1,
	       makecol(0,0,0));

      int ix = pw->getX() / 16;
      int iy = pw->getY() / 16;
      int ixx = (pw->getX() + pw->getSize() - 1) / 16;
      int iyy = (pw->getY() + pw->getSize() - 1) / 16;
      for(int i = ix; i <= ixx; i++)
  	for(int j = iy; j <= iyy; j++)
  	  if(terrains[i][j] != NULL && terrains[i][j]->getLevel() != 0) // todo not so sure its still ok (level)
  	    masked_blit(terrains[i][j]->getBuffer(),buffer,0,0,i*16,j*16,16,16);
    }

  // handle intents + terrain collisions
  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
    {
      Wrapper * pw = it->getWrapper();

      int intent = pw->move();
      // todo: handle death ?
      // if(intent == 0 || pw->getDirection() == intent) // abs(diff)==2 todo
      if(intent == 0 || pw->getDirection() == intent || abs(pw->getDirection() - intent) == 2) // abs(diff)==2
  	switch(intent)
  	  {
  	  case 1:
  	    pw->setNewY(pw->getY()-pw->getSpeed());
  	    break;
  	  case 2:
  	    pw->setNewX(pw->getX()+pw->getSpeed());
  	    break;
  	  case 3:
  	    pw->setNewY(pw->getY()+pw->getSpeed());
  	    break;
  	  case 4:
  	    pw->setNewX(pw->getX()-pw->getSpeed());
  	  }
      else
  	{
  	  pw->setNewX(round((double)pw->getX() / 16) * 16);
  	  pw->setNewY(round((double)pw->getY() / 16) * 16);
  	}

      if(intent)
  	pw->setNewDirection(intent);
      
      // map bounds
      if(pw->getNewX() < 0 || pw->getNewX() + pw->getSize() > width * 16 || pw->getNewY() < 0 || pw->getNewY() + pw->getSize() > height * 16)
  	{
  	  pw->resetChanges();
  	  continue;
  	}

      // terrain collisions
      // todo handle bangs
      int ix = pw->getNewX() / 16;
      int iy = pw->getNewY() / 16;
      int ixx = (pw->getNewX() + pw->getSize() - 1) / 16;
      int iyy = (pw->getNewY() + pw->getSize() - 1) / 16;
      bool collision = false;
      for(int i = ix; i <= ixx && !collision; i++)
  	for(int j = iy; j <= iyy && !collision; j++)
  	  if(terrains[i][j] != NULL && terrains[i][j]->isCollisionable())
  	    collision = true;
      if(collision)
  	{
  	  pw->resetChanges();
  	  continue;
  	}
    }

  // object vs object collisions
  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
    for(list<WrapperBox>::iterator itt = objects.begin(); itt != objects.end(); itt++)
      {
  	if(it != itt)
  	  {
	    Wrapper * pw1 = it->getWrapper();
	    Wrapper * pw2 = itt->getWrapper();

	    if(!pw1->isCollisionable() || !pw2->isCollisionable())
	      continue;

	    // handle complex collisions todo

  	    int x11 = pw1->getNewX();
  	    int y11 = pw1->getNewY();
  	    int x12 = pw1->getNewX() + pw1->getSize() - 1;
  	    int y12 = pw1->getNewY() + pw1->getSize() - 1;

  	    int x21 = pw2->getNewX();
  	    int y21 = pw2->getNewY();
  	    int x22 = pw2->getNewX() + pw2->getSize() - 1;
  	    int y22 = pw2->getNewY() + pw2->getSize() - 1;

  	    if(detectRectsCollision(x11,y11,x12,y12,x21,y21,x22,y22))
  	      {
		// todo handle bangs
  		pw1->resetChanges();
  		pw2->resetChanges();
  	      }
  	  }
      }

  // redraw
  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
    {
      Wrapper * pw = it->getWrapper();

      pw->applyChanges();

      masked_blit(pw->getBuffer(),buffer,0,0,pw->getX(),pw->getY(),pw->getSize(),pw->getSize());

      int ix = pw->getX() / 16;
      int iy = pw->getY() / 16;
      int ixx = (pw->getX() + pw->getSize() - 1) / 16;
      int iyy = (pw->getY() + pw->getSize() - 1) / 16;
      for(int i = ix; i <= ixx; i++)
  	for(int j = iy; j <= iyy; j++)
  	  if(terrains[i][j] != NULL && terrains[i][j]->getLevel() == 1)
  	    masked_blit(terrains[i][j]->getBuffer(),buffer,0,0,i*16,j*16,16,16);
    }
}

Point TutorialMap::getFocus()
{
  list<WrapperBox>::iterator it = objects.begin();
  Wrapper * pw = it->getWrapper();
  return Point(pw->getX() + 16, pw->getY() + 16);
}

void TutorialMap::addTank(Tank * tank)
{
  // todo: check if randed spot is not in collision with tank/bullet in move

  bool spotMap[width][height];

  for(int i = 0; i < width; i++)
    for(int j = 0; j < height; j++)
      spotMap[i][j] = false;

  for(int i = 0; i < width; i++)
    for(int j = 0; j < height; j++)
      if(terrains[i][j] == NULL || terrains[i][j]->isSpawnable())
	spotMap[i][j] = true;

  list<Point> spots;

  for(int i = 0; i < width - 1; i++)
    for(int j = 0; j < height - 1; j++)
      {
	bool spot = true;
	for(int ii = 0; ii < 2; ii++)
	  for(int jj = 0; jj < 2; jj++)
	    if(!spotMap[i+ii][j+jj])
	      spot = false;

	if(spot)
	  {
	    spots.push_back(Point(i*16,j*16));
	    for(int ii = 0; ii < 2; ii++)
	      for(int jj = 0; jj < 2; jj++)
		spotMap[i+ii][j+jj] = false;
	  }
      }

  if(!spots.size())
    throw new Exception("Can not find spawn spot");

  // before rand, delete spots that colliding with MapObjects

  int rnd = rand() % spots.size();
  list<Point>::iterator it = spots.begin();

  for(int i = 0; i < rnd; i++)
    it++;

  objects.push_back(WrapperBox(new TankWrapper(it->getX(),it->getY(),1,tank))); // get this 1 from tank
}

bool TutorialMap::detectRectsCollision(int x11, int y11, int x12, int y12,
				       int x21, int y21, int x22, int y22)
{
  if((x11 <= x21 && x21 <= x12 && y11 <= y21 && y21 <= y12) ||
     (x11 <= x21 && x21 <= x12 && y11 <= y22 && y22 <= y12) ||
     (x11 <= x22 && x22 <= x12 && y11 <= y22 && y22 <= y12) ||
     (x11 <= x22 && x22 <= x12 && y11 <= y21 && y21 <= y12))
    return true;

  return false;
}
