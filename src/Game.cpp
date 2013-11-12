#include "Game.hpp"
#include "TutorialMode.hpp"

Game::Game(BITMAP * screen)
{
  this->screen = screen;
  mode = NULL;
  menu = new Menu(screen);

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
      menu->toggle();
    }

  if(!key[KEY_ESC] && escPressed)
    escPressed = false;

  if(menu->isOn())
    {
      menu->move();

      switch(menu->getOption())
	{
	case 1:
	  mode = new TutorialMode(screen);
	  menu->toggle();
	  break;
	case 1337:
	  done = true;
	  break;
	}

      return;
    }

  if(!menu->isOn() && mode != NULL)
    {
      mode->move();
      return;
    }
}

void Game::draw()
{
  if(menu->isOn())
    {
      menu->draw();
      return;
    }

  if(!menu->isOn() && mode != NULL)
    {
      mode->draw();
      return;
    }
}

bool Game::isDone()
{
  return done;
}
