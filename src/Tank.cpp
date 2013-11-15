#include <sstream>

#include "Tank.hpp"
#include "LineBullet.hpp"

using namespace std;

Tank::Tank(Spriter * spriter)
{
  this->spriter = spriter;
  buffer = NULL;

  bullet = NULL;
  rotation = 1;
  offset = 0;
  burn = false;

  hp = 1;
  hpMax = 1;
  ammo = 10;
  ammoMax = 10;
  fuel = 100;
  fuelMax = 100;
  reload = 0;
  reloadMax = 10;
}

Tank::Tank(Spriter * spriter, int rotation,
	   int hp, int hpMax,
	   int ammo, int ammoMax,
	   int fuel, int fuelMax,
	   int reload, int reloadMax)
{
  this->spriter = spriter;
  buffer = NULL;

  bullet = NULL;
  this->rotation = rotation;
  offset = 0;
  burn = false;

  this->hp = hp;
  this->hpMax = hpMax;
  this->ammo = ammo;
  this->ammoMax = ammoMax;
  this->fuel = fuel;
  this->fuelMax = fuelMax;
  this->reload = reload;
  this->reloadMax = reloadMax;
}

Tank::~Tank()
{
}

void Tank::update()
{
  reload = reload > 0 ? reload - 1 : 0;
  offset = (offset + 1) % 2;
}

void Tank::shoot()
{
  if(!reload && ammo > 0)
    {
      bullet = new LineBullet(spriter,getRotation());
      ammo--;
      reload = reloadMax;
    }
}

bool Tank::isLocked()
{
  return fuel ? false : true;
}

Spriter * Tank::getSpriter()
{
  return spriter;
}

BITMAP * Tank::getBuffer()
{
  return buffer;
}

Bullet * Tank::breed()
{
  if(bullet)
    {
      Bullet * tmp = bullet;
      bullet = NULL;
      return tmp;
    }

  return NULL;
}

void Tank::hurt(int power)
{
  hp = hp - power < 0 ? 0 : hp - power;
}

void Tank::burnFuel(int amount)
{
  fuel = fuel - amount < 0 ? 0 : fuel - amount;
}

void Tank::addAmmo(int amount)
{
  ammo = ammo + amount > ammoMax ? ammoMax : ammo + amount;
}

void Tank::addFuel(int amount)
{
  fuel = fuel + amount > fuelMax ? fuelMax : fuel + amount;
}

int Tank::getHp()
{
  return hp;
}

int Tank::getHpMax()
{
  return hpMax;
}

int Tank::getAmmo()
{
  return ammo;
}

int Tank::getAmmoMax()
{
  return ammoMax;
}

int Tank::getFuel()
{
  return fuel;
}

int Tank::getFuelMax()
{
  return fuelMax;
}

int Tank::getReload()
{
  return reload;
}

int Tank::getReloadMax()
{
  return reloadMax;
}

int Tank::getRotation()
{
  return rotation;
}

int Tank::getId()
{
  return 7;
}

bool Tank::isDeath()
{
  return hp ? false : true;
}

bool Tank::isBurning()
{
  return burn;
}

string Tank::toString()
{
  ostringstream oss;

  oss << "HP: " << hp << "/" << hpMax;
  oss << " AMMO: " << ammo << "/" << ammoMax;
  oss << " FUEL: " << fuel << "/" << fuelMax;
  oss << " RELOAD: " << reload << "/" << reloadMax;

  return oss.str();
}
