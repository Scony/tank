#ifndef TANK_HPP
#define TANK_HPP

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
  bool burn;

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

  bool isDeath();
  bool isBurning();

  virtual int move() = 0;
  Bullet * breed();
  void hurt(int power);
  void burnFuel(int amount);

  void addAmmo(int amount);
  void addFuel(int amount);

  int getHp();
  int getHpMax();
  int getAmmo();
  int getAmmoMax();
  int getFuel();
  int getFuelMax();
  int getReload();
  int getReloadMax();

  int getRotation();
  virtual int getId();
};

#endif
