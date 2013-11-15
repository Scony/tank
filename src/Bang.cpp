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

int Bang::getId()
{
  return 11;
}
