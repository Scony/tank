#include "SimpleBang.hpp"

SimpleBang::SimpleBang(Spriter * spriter) :
  Bang(spriter)
{
  buffer = spriter->getBang(0);
  death = false;
  stance = 0;
  latency = 10;
}

SimpleBang::~SimpleBang()
{
}

int SimpleBang::move()
{
  if(!--latency)
    {
      latency = 10;
      if(++stance >= 2)
	death = true;
      else
	buffer = spriter->getBang(stance);
    }

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
