#include "Menu.hpp"
#include "Exception.hpp"

using namespace std;

Menu::Menu(BITMAP * screen)
{
  this->screen = screen;
  buffer = create_bitmap(200,200);

  selected = 1;
  approved = false;
  upPressed = key[KEY_UP] ? true : false;
  downPressed = key[KEY_DOWN] ? true : false;

  options.push_back("Roulette");
  options.push_back("Tutorial");
  options.push_back("Editor");
  options.push_back("Exit");
}

Menu::~Menu()
{
  destroy_bitmap(buffer);
}

void Menu::move()
{
  if(key[KEY_ENTER])
    {
      approved = true;
    }

  if(key[KEY_UP])
    {
      if(!upPressed)
	{
	  selected = selected - 1 < 1 ? (int)options.size() : selected - 1;
	  upPressed = true;
	}
    }
  else
    upPressed = false;

  if(key[KEY_DOWN])
    {
      if(!downPressed)
	{
	  selected = selected + 1 > (int)options.size() ? 1 : selected + 1;
	  downPressed = true;
	}
    }
  else
    downPressed = false;
}

void Menu::draw()
{
  clear_to_color(buffer,makecol(25,25,25));

  int i = 1;
  for(list<string>::iterator it = options.begin(); it != options.end(); it++)
    {
      if(i == selected)
	textout_ex(buffer,font,it->c_str(),20,30*i,makecol(255,255,255),makecol(100,100,100));
      else
	textout_ex(buffer,font,it->c_str(),20,30*i,makecol(255,255,255),-1);
      i++;
    }

  blit(buffer,screen,0,0,screen->w/2-100,screen->h/2-100,buffer->w,buffer->h);
}

int Menu::getOption()
{
  if(approved)
    {
      approved = false;
      return selected;
    }

  return 0;
}
