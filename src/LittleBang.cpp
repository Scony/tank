#include "LittleBang.hpp"

LittleBang::LittleBang(Spriter * spriter) :
  Bang(spriter)
{
  buffer = spriter->getBang(0);
  death = false;
  latency = 10;
}

LittleBang::~LittleBang()
{
}

int LittleBang::move()
{
  if(!--latency)
    death = true;

  return 0;
}

int LittleBang::getId()
{
  return 13;
}

bool LittleBang::isDeath()
{
  return death;
}
