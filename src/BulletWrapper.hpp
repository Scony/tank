#ifndef BULLET_WRAPPER_HPP
#define BULLET_WRAPPER_HPP

#include "Wrapper.hpp"
#include "Bullet.hpp"

class BulletWrapper : public Wrapper
{
  Bullet * bullet;
  bool visible;
  bool death;
public:
  BulletWrapper(int x, int y, int direction, Bullet * bullet);
  ~BulletWrapper();

  int move();
  void bang();
  Wrapper * breed();

  Bullet * getBullet();
  BITMAP * getBuffer();
  int getSize();
  int getSpeed();
  int getId();
  int getResistance();
  int getPower();

  bool isVisible();
  bool isDeath();
  bool isBangMaker();
};

#endif
