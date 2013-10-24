#include "FreeGame.hpp"
#include "StaticMap.hpp"

FreeGame::FreeGame(BITMAP * screen) : Game(screen)
{
  spriter = new Spriter("sprite.bmp");
  map = new StaticMap(...);	// todo
}

FreeGame::~FreeGame()
{
  delete map;
  delete spriter;
}

void FreeGame::move()
{
  // 
}

void FreeGame::draw()
{
  blit(map->getBuffer(),
       screen,
       map->getX(),
       map->getY(),
       0,0,
       map->getW(),
       map->getH());
}
