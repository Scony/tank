#include "Game.hpp"
#include "TutorialMode.hpp"

Game::Game(BITMAP * screen)
{
  this->screen = screen;
  mode = new TutorialMode(screen);
  menu = true;
  if(key[KEY_ESC])
    flag = true;
  else
    flag = false;

  mode->move();
  mode->draw();
}

Game::~Game()
{
  delete mode;
}

void Game::move()
{
  if(key[KEY_ESC] && !flag)
    {
      flag = true;
      menu = !menu;
    }
  if(!key[KEY_ESC] && flag)
    flag = false;

  if(!menu)
    mode->move();
  else
    {
      if(key[KEY_X])
	exit(0);
      rectfill( screen, (screen->w-200)/2, (screen->h-200)/2, (screen->w+200)/2, (screen->h+200)/2, makecol( 255, 150, 0 ) );
      textout_ex( screen, font, "Witaj w Allegro !", (screen->w-200)/2+20, (screen->h-200)/2+20, makecol( 255, 0, 255 ), - 1 );
      textout_ex( screen, font, "Witaj w Allegro !", (screen->w-200)/2+20, (screen->h-200)/2+50, makecol( 255, 0, 255 ), makecol( 255, 255, 255 ) );
      textout_ex( screen, font, "Witaj w Allegro !", (screen->w-200)/2+20, (screen->h-200)/2+80, makecol( 255, 0, 255 ), - 1 );
    }
}

void Game::draw()
{
  if(!menu)
    mode->draw();
}
