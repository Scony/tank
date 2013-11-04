#ifndef BULLET_WRAPPER_HPP
#define BULLET_WRAPPER_HPP

#include "Wrapper.hpp"
#include "Bullet.hpp"

class BulletWrapper : public Wrapper
{
  Bullet * bullet;
public:
  BulletWrapper(int x, int y, int direction, Bullet * bullet);
  ~BulletWrapper();

  int move();

  Bullet * getBullet();
  BITMAP * getBuffer();
  int getSize();

  bool isClerable();
  bool isDeath();
  bool isCollisionable();
};

#endif
