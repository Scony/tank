#include <sstream>
#include <stdlib.h>

#include "Game.hpp"

using namespace std;

int Game::gidc = 0;

Game::Game()
{
  gid = ++gidc;
  // load map here
  // make tanks and place em in tha map
  for(int i = 0; i < GAME_SIZE; i++)
    tanks.push_back(Tank(i,rand()%500,rand()%500,0,0));
}

void Game::updateTank(int id, int x, int y, int rotation, int shoot)
{
  for(list<Tank>::iterator i = tanks.begin(); i != tanks.end(); i++)
    if(i->getId() == id)
      *i = Tank(id,x,y,rotation,shoot);
}

void Game::deleteTank(int id)
{
  for(list<Tank>::iterator i = tanks.begin(); i != tanks.end(); i++)
    if(i->getId() == id)
      {
	tanks.erase(i);
	break;
      }
}

bool Game::isOver()
{
  return !tanks.size();
}

std::string Game::getInitData(int id)
{
  stringstream ss;
  ss << "MAP STUFF\n"; // map
  for(list<Tank>::iterator i = tanks.begin(); i != tanks.end(); i++)
    if(i->getId() == id)
      {
	ss << gid << " " << i->toString();
	return ss.str();
      }

  return "ERROR INIT\n";
}

std::string Game::getData()
{
  stringstream ss;

  if(!isOver())
    {
      ss << gid << " " << tanks.size();
      for(list<Tank>::iterator i = tanks.begin(); i != tanks.end(); i++)
	ss << endl << i->toString();
    }
  else
    ss << 0;

  return ss.str();
}

int Game::getId()
{
  return gid;
}
