#include <sstream>

#include "Tank.hpp"

using namespace std;

Tank::Tank(int id, int x, int y, int rotation, int shoot)
{
  this->id = id;
  this->x = x;
  this->y = y;
  this->rotation = rotation;
  this->shoot = shoot;
}

int Tank::getId()
{
  return id;
}

string Tank::toString()
{
  stringstream ss;
  ss << id << " " << x << " " << y << " " << rotation << " " << shoot;
  
  return ss.str();
}
