#include "TestGame2.hpp"
#include "TestMap.hpp"

TestGame2::TestGame2(BITMAP * screen) : Game(screen)
{
  spriter = new Spriter("sprite.bmp");
  map = new TestMap(spriter,50,38);
}

TestGame2::~TestGame2()
{
  delete map;
  delete spriter;
}

void TestGame2::move()
{
  map->move();
}

void TestGame2::draw()
{
  blit(map->getBuffer(),
       screen,
       0,0,
       0,0,
       screen->w,
       screen->h);
}
