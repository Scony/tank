#include "TestGame.hpp"

TestGame::TestGame(BITMAP * screen) : Game(screen)
{
  sp = new Spriter("sprite.bmp");
  buffer = create_bitmap(screen->w,screen->h);
  clear_to_color(buffer,makecol(0,0,0));
  blit(sp->getTerrain(0),buffer,0,0,0,0,16,16);
}

TestGame::~TestGame()
{
  destroy_bitmap(buffer);
}

void TestGame::move()
{
  clear_to_color(buffer,makecol(0,0,0));
  blit(sp->getTerrain(0),buffer,0,0,16*(rand()%10),16*(rand()%10),16,16);
}

void TestGame::draw()
{
  blit(buffer,screen,0,0,0,0,buffer->w,buffer->h);
}
