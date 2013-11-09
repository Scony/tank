#include <fstream>
#include <math.h>
#include <stdio.h>

#include "TutorialMap.hpp"
#include "BrickTerrain.hpp"
#include "ConcreteTerrain.hpp"
#include "PavementTerrain.hpp"
#include "BushTerrain.hpp"
#include "WaterTerrain.hpp"
#include "TankWrapper.hpp"

using namespace std;

TutorialMap::TutorialMap(Spriter * spriter, PolicyManager * policy, string fileName)
{
  this->spriter = spriter;
  this->policy = policy;

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
  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
    delete it->getWrapper();

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
  // debug
  // rest(500);

  // clear objects
  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
    {
      Wrapper * pw = it->getWrapper();

      if(!pw->isVisible())
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
      	  if(0 <= i && i < width && 0 <= j && j < height && terrains[i][j] != NULL)
      	    masked_blit(terrains[i][j]->getBuffer(),buffer,0,0,i*16,j*16,16,16);
    }

  // handle breeds
  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
    {
      Wrapper * pw = it->getWrapper();
      Wrapper * born = pw->breed();

      if(born)
	objects.push_back(born);
    }

  // handle dies
  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end();)
    {
      Wrapper * pw = it->getWrapper();

      if(pw->isDeath())
	{
	  delete pw;
	  it = objects.erase(it);
	}
      else
	it++;
    }      

  // handle moves (intents)
  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
    {
      Wrapper * pw = it->getWrapper();

      int intent = pw->move();
      if(intent == 0 || pw->getDirection() == intent || abs(pw->getDirection() - intent) == 2)
  	switch(intent)
  	  {
  	  case 1:
  	    pw->setNewY(pw->getY() - pw->getSpeed());
  	    break;
  	  case 2:
  	    pw->setNewX(pw->getX() + pw->getSpeed());
  	    break;
  	  case 3:
  	    pw->setNewY(pw->getY() + pw->getSpeed());
  	    break;
  	  case 4:
  	    pw->setNewX(pw->getX() - pw->getSpeed());
  	  }
      else
  	{
  	  pw->setNewX(round((double)pw->getX() / 16) * 16);
  	  pw->setNewY(round((double)pw->getY() / 16) * 16);
  	}

      if(intent)
  	pw->setNewDirection(intent);
    }

  // object vs map bounds collisions
  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
    {
      Wrapper * pw = it->getWrapper();

      if(!policy->checkCollisionability(0,pw->getId()))
	continue;

      if(pw->getNewX() < 0 || pw->getNewX() + pw->getSize() > width * 16 || pw->getNewY() < 0 || pw->getNewY() + pw->getSize() > height * 16)
	{
	  if(pw->isBangMaker())
	    pw->bang();
	  else
	    pw->resetChanges();
	}
    }

  // object vs terrains collisions
  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
    {
      Wrapper * pw = it->getWrapper();

      int ix = pw->getNewX() / 16;
      int iy = pw->getNewY() / 16;
      int ixx = (pw->getNewX() + pw->getSize() - 1) / 16;
      int iyy = (pw->getNewY() + pw->getSize() - 1) / 16;

      bool collision = false;

      for(int i = ix; i <= ixx; i++)
  	for(int j = iy; j <= iyy; j++)
  	  if(0 <= i && i < width && 0 <= j && j < height &&
	     terrains[i][j] != NULL && policy->checkCollisionability(terrains[i][j]->getId(),pw->getId()))
	    {
	      if(pw->isBangMaker())
		{
		  pw->bang();
		  if(terrains[i][j]->getResistance() < pw->getPower())
		    {
		      // todo: put into function
		      delete terrains[i][j];
		      terrains[i][j] = NULL;
		      rectfill(buffer,
			       i*16,
			       j*16,
			       i*16 + 16 - 1,
			       j*16 + 16 - 1,
			       makecol(0,0,0));
		    }
		}

	      collision = true;
	    }

      if(collision)
	pw->resetChanges();
    }

  // object vs object collisions
  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
    for(list<WrapperBox>::iterator itt = objects.begin(); itt != objects.end(); itt++)
      {
  	if(it != itt)
  	  {
	    Wrapper * pw1 = it->getWrapper();
	    Wrapper * pw2 = itt->getWrapper();

	    if(!policy->checkCollisionability(pw1->getId(),pw2->getId()))
	      continue;

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
		if(pw1->isBangMaker() && pw2->isBangMaker())
		  {
		    pw1->bang();
		    pw2->bang();
		    continue;
		  }

		if(pw1->isBangMaker())
		  {
		    pw1->bang();
		    if(pw1->getPower() > pw2->getResistance())
		      pw2->bang();
		    continue;
		  }

		if(pw2->isBangMaker())
		  {
		    pw2->bang();
		    if(pw2->getPower() > pw1->getResistance())
		      pw1->bang();
		    continue;
		  }

		int ox11 = pw1->getX();
		int oy11 = pw1->getY();
		int ox12 = pw1->getX() + pw1->getSize() - 1;
		int oy12 = pw1->getY() + pw1->getSize() - 1;

		int ox21 = pw2->getX();
		int oy21 = pw2->getY();
		int ox22 = pw2->getX() + pw2->getSize() - 1;
		int oy22 = pw2->getY() + pw2->getSize() - 1;

		bool n1o2 = detectRectsCollision(x11,y11,x12,y12,ox21,oy21,ox22,oy22);
		bool o1n2 = detectRectsCollision(ox11,oy11,ox12,oy12,x21,y21,x22,y22);

		if(n1o2)
		  {
		    if(o1n2)
		      {
			pw1->resetChanges();
			pw2->resetChanges();
		      }
		    else
		      {
			pw1->resetChanges();
		      }
		  }
		else
		  {
		    if(o1n2)
		      {
			pw2->resetChanges();
		      }
		    else
		      {
			pw1->resetChanges();
			pw2->resetChanges();
		      }
		  }
  	      }
  	  }
      }

  // apply changes

  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
    {
      Wrapper * pw = it->getWrapper();

      pw->applyChanges();
    }

  // redraw
  // if needed then todo: complex overlay algorithm
  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
    {
      Wrapper * pw = it->getWrapper();

      if(!pw->isVisible())
	continue;

      masked_blit(pw->getBuffer(),buffer,0,0,pw->getX(),pw->getY(),pw->getSize(),pw->getSize());

      int ix = pw->getX() / 16;
      int iy = pw->getY() / 16;
      int ixx = (pw->getX() + pw->getSize() - 1) / 16;
      int iyy = (pw->getY() + pw->getSize() - 1) / 16;
      for(int i = ix; i <= ixx; i++)
      	for(int j = iy; j <= iyy; j++)
      	  if(0 <= i && i < width && 0 <= j && j < height &&
      	     terrains[i][j] != NULL && policy->checkOverlapability(terrains[i][j]->getId(),pw->getId()))
      	    masked_blit(terrains[i][j]->getBuffer(),buffer,0,0,i*16,j*16,16,16);
    }
}

Point TutorialMap::getFocus()
{
  list<WrapperBox>::iterator it = objects.begin();
  if(it == objects.end())
    return Point(0,0);

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
      if(terrains[i][j] == NULL || !policy->checkCollisionability(terrains[i][j]->getId(),tank->getId()))
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
