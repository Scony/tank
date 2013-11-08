#include "SimpleBang.hpp"

SimpleBang::SimpleBang(Spriter * spriter) :
  Bang(spriter)
{
  buffer = spriter->getBang(0);
  death = false;
  stance = 0;
}

SimpleBang::~SimpleBang()
{
}

int SimpleBang::move()
{
  if(++stance >= 300)
    death = true;
  else
    buffer = spriter->getBang(stance/100);

  return 0;
}

int SimpleBang::getId()
{
  return 12;
}

bool SimpleBang::isDeath()
{
  return death;
}
