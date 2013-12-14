#ifndef POINT_HPP
#define POINT_HPP

class Point
{
  int x;
  int y;
public:
  Point(int x, int y);
  ~Point();
  void setX(int x);
  void setY(int y);
  int getX();
  int getY();
};

#endif
