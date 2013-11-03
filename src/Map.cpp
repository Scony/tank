#include "Map.hpp"

Map::Map(Spriter * spriter, int width, int height)
{
  this->spriter = spriter;
  this->width = width;
  this->height = height;

  buffer = create_bitmap(width*16,height*16); // HARDCODE ! todo
  if(!buffer)
    throw new Exception("Can not create bitmap");
}

Map::Map()
{
}

Map::~Map()
{
  destroy_bitmap(buffer);
}

BITMAP * Map::getBuffer()
{
  return buffer;
}
