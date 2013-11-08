#include "Bang.hpp"

Bang::Bang(Spriter * spriter)
{
  this->spriter = spriter;
  buffer = NULL;
}

Bang::~Bang()
{
}

BITMAP * Bang::getBuffer()
{
  return buffer;
}

int Bang::getSize()
{
  return spriter->getBangSize();
}

int Bang::getId()
{
  return 11;
}
