#include "Map.hpp"
#include "Configuration.hpp"

Map::Map(Spriter * spriter, int width, int height)
{
  this->spriter = spriter;
  this->width = width;
  this->height = height;

  buffer = create_bitmap(width * Configuration::getInstance()->getMedium(),
			 height * Configuration::getInstance()->getMedium());
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
