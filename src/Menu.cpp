#include "Menu.hpp"

using namespace std;

Menu::Menu(BITMAP * screen)
{
  this->screen = screen;

  on = true;
  selected = 1;
  option = 0;
  options.push_back("Test");
  options.push_back("Exit");
}

Menu::~Menu()
{
}

void Menu::move()
{
  if(key[KEY_ENTER])
    {
      if(selected == (int)options.size())
	option = 1337;
      else
	option = selected;
    }

  if(key[KEY_UP])
    {
      selected = selected - 1 < 1 ? 1 : selected - 1;
    }

  if(key[KEY_DOWN])
    {
      selected = selected + 1 > (int)options.size() ? (int)options.size() : selected + 1;
    }
}

void Menu::draw()
{
  rectfill( screen, (screen->w-200)/2, (screen->h-200)/2, (screen->w+200)/2, (screen->h+200)/2, makecol( 255, 150, 0 ) );

  int i = 1;
  for(list<string>::iterator it = options.begin(); it != options.end(); it++)
    {
      if(i == selected)
	textout_ex( screen, font, it->c_str(), (screen->w-200)/2+20, (screen->h-200)/2+30*i, makecol( 255, 0, 255 ), makecol( 255, 255, 255 ) );
      else
	textout_ex( screen, font, it->c_str(), (screen->w-200)/2+20, (screen->h-200)/2+30*i, makecol( 255, 0, 255 ), -1 );
      i++;
    }
}

void Menu::toggle()
{
  on = !on;
}

int Menu::getOption()
{
  int tmp = option;
  option = 0;

  return tmp;
}

bool Menu::isOn()
{
  return on;
}
