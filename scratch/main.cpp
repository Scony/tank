#include "Game.hpp"
#include "Test.hpp"
#include <stdio.h>

volatile long speed = 0;

void increment_speed()
{
  speed++;
}
END_OF_FUNCTION(increment_speed);

LOCK_VARIABLE(speed);
LOCK_FUNCTION(increment_speed);

int main()
{
  allegro_init();
  install_keyboard();
  install_timer();
  install_int_ex(increment_speed,BPS_TO_TIMER(100));
  set_color_depth(32);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,608,0,0);
  clear_to_color(screen,makecol(0,0,0));

  Game * game = new Test(800,608);

  while(1)
    {
      for(;speed > 0;speed--)
	{
	  game->move();
	  blit(game->getBuffer(),screen,0,0,0,0,800,608);
	  printf("%d %d\n",screen->w,screen->h);
	}
    }

  delete game;
  remove_int(increment_speed);
  allegro_exit();
  return 0;
}

END_OF_MAIN();
