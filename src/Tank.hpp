#ifndef TANK_HPP
#define TANK_HPP

#include <iostream>
#include <allegro.h>

#include "Spriter.hpp"
#include "Bullet.hpp"

class Tank
{
  int hp;
  int hpMax;
  int ammo;
  int ammoMax;
  int fuel;
  int fuelMax;
  int reload;
  int reloadMax;

protected:
  Spriter * spriter;
  BITMAP * buffer;

  Bullet * bullet;
  int rotation;
  int offset;

  void update();
  void shoot();

  bool isLocked();

public:
  Tank(Spriter * spriter);
  Tank(Spriter * spriter, int rotation,
       int hp, int hpMax,
       int ammo, int ammoMax,
       int fuel, int fuelMax,
       int reload, int reloadMax);
  virtual ~Tank();
  Spriter * getSpriter();
  BITMAP * getBuffer();

  virtual int move() = 0;
  Bullet * breed();
  void hurt(int power);
  void burnFuel(int amount);

  int getRotation();
  virtual int getId();

  bool isDeath();

  std::string toString();
};

#endif
