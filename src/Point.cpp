#include "Point.hpp"

Point::Point(int x, int y)
{
  this->x = x;
  this->y = y;
}

Point::~Point()
{
}

void Point::setX(int x)
{
  this->x = x;
}

void Point::setY(int y)
{
  this->y = y;
}

int Point::getX()
{
  return x;
}

int Point::getY()
{
  return y;
}
