#ifndef MENU_HPP
#define MENU_HPP

#include <allegro.h>
#include <list>
#include <iostream>

class Menu
{
protected:
  BITMAP * screen;
  BITMAP * buffer;

  int selected;
  bool approved;
  std::list<std::string> options;
  bool upPressed;
  bool downPressed;
public:
  Menu(BITMAP * screen);
  ~Menu();

  void move();
  void draw();

  int getOption();
};

#endif
