#ifndef LINE_BULLET_HPP
#define LINE_BULLET_HPP

#include "Bullet.hpp"

class LineBullet : public Bullet
{
  int intent;
  int lifetime;
public:
  LineBullet(Spriter * spriter, int intent);
  ~LineBullet();

  bool isDeath();

  int move();

  int getId();
  int getPower();
};

#endif
