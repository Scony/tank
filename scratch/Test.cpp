#include "Test.hpp"

Test::Test(int w, int h) : Game(w,h)
{
  clear_to_color(buffer,makecol(0,0,0));
  blit(ld.getTerrain(0),buffer,0,0,0,0,16,16);
}

Test::~Test()
{
}

void Test::move()
{
  clear_to_color(buffer,makecol(0,0,0));
  blit(ld.getTerrain(0),buffer,0,0,16*(rand()%10),16*(rand()%10),16,16);
}
