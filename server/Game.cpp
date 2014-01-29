#include <sstream>
#include <stdlib.h>

#include "Game.hpp"

using namespace std;

int Game::gidc = 0;

Game::Game() : map("medium.map")
{
  gid = ++gidc;
  for(int i = 0; i < GAME_SIZE; i++)
    {
      pair<int,int> ab = map.getTankPosition();
      tanks.push_back(Tank(i,ab.first,ab.second,0,0,"unknown",0,255,0,0));
    }
}

void Game::updateTank(int id, int x, int y, int rotation, int shoot, string nick, int r, int g, int b, int frags)
{
  for(list<Tank>::iterator i = tanks.begin(); i != tanks.end(); i++)
    if(i->getId() == id)
      *i = Tank(id,x,y,rotation,shoot,nick,r,g,b,frags);
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
  ss << map.getData() << endl;
  for(list<Tank>::iterator i = tanks.begin(); i != tanks.end(); i++)
    if(i->getId() == id)
      {
	ss << gid << " " << i->toString();
	return ss.str();
      }

  return "INIT ERROR\n";
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
