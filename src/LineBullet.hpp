#ifndef LINE_BULLET_HPP
#define LINE_BULLET_HPP

#include "Bullet.hpp"

class LineBullet : public Bullet
{
  int intent;
public:
  LineBullet(Spriter * spriter, int intent);
  ~LineBullet();

  int move();
};

#endif
