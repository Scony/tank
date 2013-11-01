#include "Spriter.hpp"
#include "Exception.hpp"

Spriter::Spriter(std::string path)
{
  // sprite
  sprite = load_bmp(path.c_str(),default_palette);
  if(!sprite)
    throw new Exception("Can not load " + path);

  // terrain
  for(int i = 0; i < 5; i++)
    {
      terrain[i] = create_bitmap(16,16);
      blit(sprite,terrain[i],0,256+i*16,0,0,16,16);
    }

  // tank
  for(int i = 0; i < 8; i++)
    {
      tank[i] = create_bitmap(32,32);
      if(i % 2)
	blit(sprite,tank[i],32,i/2*32,0,0,32,32);
      else
	blit(sprite,tank[i],0,i/2*32,0,0,32,32);
    }

  // bang
  for(int i = 0; i < 3; i++)
    {
      bang[i] = create_bitmap(32,32);
      blit(sprite,bang[i],256+i*32,64,0,0,32,32);
    }

  // bullet
  for(int i = 0; i < 4; i++)
    {
      bullet[i] = create_bitmap(8,8);
      blit(sprite,bullet[i],i*8,352,0,0,8,8);
    }
}

Spriter::~Spriter()
{
  destroy_bitmap(sprite);
  for(int i = 0; i < 4; i++)
    {
      destroy_bitmap(terrain[i]);
      destroy_bitmap(bullet[i]);
    }
  for(int i = 0; i < 8; i++)
    destroy_bitmap(tank[i]);
  for(int i = 0; i < 3; i++)
    destroy_bitmap(bang[i]);
}

BITMAP * Spriter::getSprite()
{
  return sprite;
}

BITMAP * Spriter::getTerrain(int index)
{
  if(index >= 5 || index < 0)
    throw new Exception("Terrain index out of bounds");
  return terrain[index];
}

BITMAP * Spriter::getTank(int index)
{
  if(index >= 8 || index < 0)
    throw new Exception("Tank index out of bounds");
  return tank[index];
}

int Spriter::getTankSize()
{
  return 32;
}

int Spriter::getTerrainSize()
{
  return 16;
}
