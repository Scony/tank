#include "Game.hpp"
#include "TutorialGame.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 608
// more defines to remove hardcoded values

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
  set_gfx_mode(GFX_AUTODETECT_WINDOWED,WINDOW_WIDTH,WINDOW_HEIGHT,0,0);

  Game * game = new TutorialGame(screen);

  while(!key[KEY_ESC])
    {
      for(;speed > 0 && !key[KEY_ESC];speed--)
	{
	  game->move();
	  game->draw();
	}
    }

  delete game;
  remove_int(increment_speed);
  allegro_exit();

  return 0;
}

END_OF_MAIN();
