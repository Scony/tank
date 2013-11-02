#ifndef BOX_HPP
#define BOX_HPP

class Box
{
protected:
  // actual values
  int x;
  int y;
  int direction;

  // changes to apply or reset
  int nx;
  int ny;
  int ndirection;
public:
  Box(int x, int y, int direction);
  ~Box();

  void resetChanges();
  void applyChanges();

  int getX();
  int getY();
  int getDirection();

  int getNewX();
  void setNewX(int x);
  int getNewY();
  void setNewY(int y);
  int getNewDirection();
  void setNewDirection(int direction);
};

#endif
