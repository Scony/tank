#include <sstream>

#include "Tank.hpp"

using namespace std;

Tank::Tank(int id, int x, int y, int rotation, int shoot, std::string nick, int r, int g, int b, int frags)
{
  this->id = id;
  this->x = x;
  this->y = y;
  this->rotation = rotation;
  this->shoot = shoot;
  this->nick = nick;
  this->r = r;
  this->g = g;
  this->b = b;
  this->frags = frags;
}

int Tank::getId()
{
  return id;
}

string Tank::toString()
{
  stringstream ss;
  ss << id << " " << x << " " << y << " " << rotation << " " << shoot << " " <<
    nick << " " << r << " " << g << " " << b << " " << frags;
  
  return ss.str();
}
