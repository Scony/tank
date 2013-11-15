#include "Spriter.hpp"
#include "Exception.hpp"

Spriter::Spriter(std::string path)
{
  // sprite
  sprite = load_bmp(path.c_str(),default_palette);
  if(!sprite)
    throw new Exception("Can not load " + path);

  // convert #000000 to #ff00ff (magic pink)
  for(int i = 0; i < sprite->w; i++)
    for(int j = 0; j < sprite->h; j++)
      if(getpixel(sprite,i,j) == 0)
	putpixel(sprite,i,j,16711935);

  // terrain
  for(int i = 0; i < 5; i++)
    {
      terrain[i] = create_bitmap(16,16);
      blit(sprite,terrain[i],0,256+i*16,0,0,16,16);
    }

  // tanks
  for(int i = 0; i < 8; i++)
    {
      tank[0][i] = create_bitmap(32,32);
      if(i % 2)
	blit(sprite,tank[0][i],32,i/2*32,0,0,32,32);
      else
	blit(sprite,tank[0][i],0,i/2*32,0,0,32,32);
    }
  for(int i = 0; i < 8; i++)
    {
      tank[1][i] = create_bitmap(32,32);
      if(i % 2)
	blit(sprite,tank[1][i],32,i/2*32+128,0,0,32,32);
      else
	blit(sprite,tank[1][i],0,i/2*32+128,0,0,32,32);
    }
  for(int i = 0; i < 8; i++)
    {
      tank[2][i] = create_bitmap(32,32);
      if(i % 2)
	blit(sprite,tank[2][i],32,i/2*32+424,0,0,32,32);
      else
	blit(sprite,tank[2][i],0,i/2*32+424,0,0,32,32);
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

  // consumable
  for(int i = 0; i < 2; i++)
    {
      consumable[i] = create_bitmap(32,32);
      blit(sprite,consumable[i],128,360+i*32,0,0,32,32);
    }

  // wreck
  wreck = create_bitmap(32,32);
  blit(sprite,wreck,64,304,0,0,32,32);

  // blank
  blank = create_bitmap(32,32);
  clear_to_color(blank,makecol(0,0,0));
}

Spriter::~Spriter()
{
  destroy_bitmap(sprite);
  for(int i = 0; i < 4; i++)
    {
      destroy_bitmap(terrain[i]);
      destroy_bitmap(bullet[i]);
    }
  for(int j = 0; j < 3; j++)
    for(int i = 0; i < 8; i++)
      destroy_bitmap(tank[j][i]);
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

BITMAP * Spriter::getTank(int kind, int index)
{
  if(index >= 8 || index < 0)
    throw new Exception("Tank index out of bounds");
  if(kind < 0 || kind > 2)
    throw new Exception("Tank kind out of bounds");
  return tank[kind][index];
}

BITMAP * Spriter::getBullet(int index)
{
  if(index >= 4 || index < 0)
    throw new Exception("Bullet index out of bounds");
  return bullet[index];
}

BITMAP * Spriter::getBang(int index)
{
  if(index >= 3 || index < 0)
    throw new Exception("Bang index out of bounds");
  return bang[index];
}

BITMAP * Spriter::getConsumable(int index)
{
  if(index >= 2 || index < 0)
    throw new Exception("Consumable index out of bounds");
  return consumable[index];
}

BITMAP * Spriter::getWreck()
{
  return wreck;
}

BITMAP * Spriter::getBlank()
{
  return blank;
}
