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
#include "ConsumableWrapper.hpp"
#include "Ammo.hpp"
#include "Fuel.hpp"
#include "Configuration.hpp"

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

  buffer = create_bitmap(width * Configuration::getInstance()->getMedium(),
			 height * Configuration::getInstance()->getMedium());
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

  int consumables;
  in >> consumables;

  for(int i = 0; i < consumables; i++)
    {
      int a;
      int b;
      int kind;
      int amount;
      in >> a >> b >> kind >> amount;
      switch(kind)
	{
	case 1:
	  objects.push_back(WrapperBox(new ConsumableWrapper(a * Configuration::getInstance()->getMedium(),
							     b * Configuration::getInstance()->getMedium(),
							     1,new Ammo(spriter,amount))));
	  break;
	case 2:
	  objects.push_back(WrapperBox(new ConsumableWrapper(a * Configuration::getInstance()->getMedium(),
							     b * Configuration::getInstance()->getMedium(),1,new Fuel(spriter,amount))));
	  break;
	}
    }

  int spots;
  in >> spots;

  for(int i = 0; i < spots; i++)
    {
      int a;
      int b;
      in >> a >> b;
      this->spots.push_back(Point(a * Configuration::getInstance()->getMedium(),
				  b * Configuration::getInstance()->getMedium()));
    }

  in.close();

  // initial draw
  clear_to_color(buffer,makecol(0,0,0));
  for(int i = 0; i < width; i++)
    for(int j = 0; j < height; j++)
      {
	if(terrains[i][j])
	  masked_blit(terrains[i][j]->getBuffer(),
		      buffer,0,0,
		      i * terrains[i][j]->getSize(),
		      j * terrains[i][j]->getSize(),
		      terrains[i][j]->getSize(),
		      terrains[i][j]->getSize());
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

      int ix = pw->getX() / Configuration::getInstance()->getMedium();
      int iy = pw->getY() / Configuration::getInstance()->getMedium();
      int ixx = (pw->getX() + pw->getSize() - 1) / Configuration::getInstance()->getMedium();
      int iyy = (pw->getY() + pw->getSize() - 1) / Configuration::getInstance()->getMedium();
      for(int i = ix; i <= ixx; i++)
      	for(int j = iy; j <= iyy; j++)
      	  if(0 <= i && i < width && 0 <= j && j < height && terrains[i][j] != NULL)
      	    masked_blit(terrains[i][j]->getBuffer(),
			buffer,0,0,
			i * terrains[i][j]->getSize(),
			j * terrains[i][j]->getSize(),
			terrains[i][j]->getSize(),
			terrains[i][j]->getSize());
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
  	  pw->setNewX(round((double)pw->getX() / Configuration::getInstance()->getMedium()) * Configuration::getInstance()->getMedium());
  	  pw->setNewY(round((double)pw->getY() / Configuration::getInstance()->getMedium()) * Configuration::getInstance()->getMedium());
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

      if(pw->getNewX() < 0 || pw->getNewX() + pw->getSize() > width * Configuration::getInstance()->getMedium()
	 || pw->getNewY() < 0 || pw->getNewY() + pw->getSize() > height * Configuration::getInstance()->getMedium())
	{
	  if(pw->isPerformer())
	    pw->perform(0,0);
	  else
	    pw->resetChanges();
	}
    }

  // object vs terrains collisions
  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
    {
      Wrapper * pw = it->getWrapper();

      int ix = pw->getNewX() / Configuration::getInstance()->getMedium();
      int iy = pw->getNewY() / Configuration::getInstance()->getMedium();
      int ixx = (pw->getNewX() + pw->getSize() - 1) / Configuration::getInstance()->getMedium();
      int iyy = (pw->getNewY() + pw->getSize() - 1) / Configuration::getInstance()->getMedium();

      bool collision = false;

      for(int i = ix; i <= ixx; i++)
  	for(int j = iy; j <= iyy; j++)
  	  if(0 <= i && i < width && 0 <= j && j < height &&
	     terrains[i][j] != NULL && policy->checkCollisionability(terrains[i][j]->getId(),pw->getId()))
	    {
	      if(pw->isPerformer())
		{
		  pw->perform(0,0);
		  if(terrains[i][j]->getResistance() < pw->getPower())
		    {
		      // todo: put into function
		      delete terrains[i][j];
		      rectfill(buffer,
			       i * terrains[i][j]->getSize(),
			       j * terrains[i][j]->getSize(),
			       i * terrains[i][j]->getSize() + terrains[i][j]->getSize() - 1,
			       j * terrains[i][j]->getSize() + terrains[i][j]->getSize() - 1,
			       makecol(0,0,0));
		      terrains[i][j] = NULL;
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
		if(pw1->isPerformer() || pw2->isPerformer())
		  {
		    pw1->perform(pw2->getId(),pw2->getPower());
		    pw2->perform(pw1->getId(),pw1->getPower());
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
  // if needed then make complex overlay algorithm
  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
    {
      Wrapper * pw = it->getWrapper();

      if(!pw->isVisible())
	continue;

      masked_blit(pw->getBuffer(),buffer,0,0,pw->getX(),pw->getY(),pw->getSize(),pw->getSize());

      int ix = pw->getX() / Configuration::getInstance()->getMedium();
      int iy = pw->getY() / Configuration::getInstance()->getMedium();
      int ixx = (pw->getX() + pw->getSize() - 1) / Configuration::getInstance()->getMedium();
      int iyy = (pw->getY() + pw->getSize() - 1) / Configuration::getInstance()->getMedium();
      for(int i = ix; i <= ixx; i++)
      	for(int j = iy; j <= iyy; j++)
      	  if(0 <= i && i < width && 0 <= j && j < height &&
      	     terrains[i][j] != NULL && policy->checkOverlapability(terrains[i][j]->getId(),pw->getId()))
      	    masked_blit(terrains[i][j]->getBuffer(),
			buffer,0,0,
			i * terrains[i][j]->getSize(),
			j * terrains[i][j]->getSize(),
			terrains[i][j]->getSize(),
			terrains[i][j]->getSize());
    }
}

Point TutorialMap::getFocus()
{
  for(list<WrapperBox>::iterator it = objects.begin(); it != objects.end(); it++)
    {
      Wrapper * pw = it->getWrapper();

      if(pw->isFocusable())
	return Point(pw->getX() + pw->getSize() / 2, pw->getY() + pw->getSize() / 2);
    }

  return Point((rand() % width) * Configuration::getInstance()->getMedium() + Configuration::getInstance()->getMedium() / 2,
	       (rand() % height) * Configuration::getInstance()->getMedium() + Configuration::getInstance()->getMedium() / 2);
}

void TutorialMap::addTank(Tank * tank)
{
  if(!spots.size())
    throw new Exception("All spots expired");

  Point p = spots.front();
  spots.pop_front();

  objects.push_back(WrapperBox(new TankWrapper(p.getX(),p.getY(),tank->getRotation(),tank)));
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
