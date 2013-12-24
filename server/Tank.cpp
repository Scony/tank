#include <sstream>

#include "Tank.hpp"

using namespace std;

Tank(int id, int x, int y, int rotation, int shoot)
{
  this->id = id;
  this->x = x;
  this->y = y;
  this->rotation = rotation;
  this->shoot = shoot;
}

string toString()
{
  // 
}
