#include <iostream>

#include "Exception.hpp"
#include "Game.hpp"

volatile long speed = 0;
volatile int close_button = 0;

void close_button_handler()
{
  close_button = 1;
}
END_OF_FUNCTION(close_button_handler);

void increment_speed()
{
  speed++;
}
END_OF_FUNCTION(increment_speed);

LOCK_VARIABLE(speed);
LOCK_FUNCTION(increment_speed);
LOCK_FUNCTION(close_button_handler);

int main()
{
  allegro_init();
  install_keyboard();
  install_timer();
  install_int_ex(increment_speed,BPS_TO_TIMER(100));
  set_close_button_callback(close_button_handler);
  set_color_depth(desktop_color_depth());
  int desktopWidth, desktopHeight;
  get_desktop_resolution(&desktopWidth,&desktopHeight);
  // set_gfx_mode(GFX_AUTODETECT,desktopWidth,desktopHeight,0,0);
  set_gfx_mode(GFX_AUTODETECT,320,240,0,0);

  clear_to_color(screen,makecol(255,255,255));

  try
    {
      Game * game = new Game(screen);

      while(!close_button && !game->isDone())
	{
	  for(; speed > 0 && !close_button && !game->isDone(); speed--)
	    {
	      game->move();
	      game->draw();
	    }
	}

      delete game;
    }
  catch(Exception * e)
    {
      std::cout << e->toString() << std::endl;
      delete e;
    }

  remove_int(increment_speed);
  allegro_exit();

  return 0;
}

END_OF_MAIN();
