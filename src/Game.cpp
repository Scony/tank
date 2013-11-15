#include "Game.hpp"
#include "TutorialMode.hpp"

Game::Game(BITMAP * screen)
{
  this->screen = screen;
  mode = NULL;
  menu = new Menu(screen);

  menuOn = true;
  done = false;
  if(key[KEY_ESC])
    escPressed = true;
  else
    escPressed = false;
}

Game::~Game()
{
  delete menu;
  if(mode != NULL)
    delete mode;
}

void Game::move()
{
  if(key[KEY_ESC] && !escPressed)
    {
      escPressed = true;
      if(mode)
	menuOn = !menuOn;
    }

  if(!key[KEY_ESC] && escPressed)
    escPressed = false;

  if(menuOn)
    {
      menu->move();

      switch(menu->getOption())
	{
	case 0:
	  break;
	case 1:
	  break;
	case 2:
	  if(mode)
	    delete mode;
	  mode = new TutorialMode(screen);
	  menuOn = false;
	  break;
	case 3:
	  break;
	default:
	  done = true;
	  break;
	}

      return;
    }

  if(!menuOn && mode != NULL)
    {
      mode->move();
      return;
    }
}

void Game::draw()
{
  if(menuOn)
    {
      menu->draw();
      return;
    }

  if(!menuOn &&  mode != NULL)
    {
      mode->draw();
      return;
    }
}

bool Game::isDone()
{
  return done;
}
