#ifndef WRAPPER_HPP
#define WRAPPER_HPP

#include <allegro.h>

class Wrapper
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
  Wrapper(int x, int y, int direction);
  virtual ~Wrapper();

  virtual bool isVisible() = 0;
  virtual bool isDeath() = 0;
  virtual bool isPerformer() = 0;
  virtual bool isFocusable() = 0;

  virtual int move() = 0;
  virtual void perform(int key, int value) = 0;
  virtual Wrapper * breed() = 0;

  void resetChanges();
  virtual void applyChanges();

  int getX();
  int getY();
  int getDirection();
  virtual int getSize() = 0;
  virtual int getSpeed() = 0;
  virtual BITMAP * getBuffer() = 0;
  virtual int getId() = 0;
  virtual int getPower() = 0;

  int getNewX();
  void setNewX(int x);
  int getNewY();
  void setNewY(int y);
  int getNewDirection();
  void setNewDirection(int direction);
};

#endif
