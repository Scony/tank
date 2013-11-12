#ifndef MENU_HPP
#define MENU_HPP

#include <allegro.h>
#include <list>
#include <iostream>

class Menu
{
protected:
  BITMAP * screen;

  bool on;
  int selected;
  int option;
  std::list<std::string> options;
public:
  Menu(BITMAP * screen);
  ~Menu();

  void move();
  void draw();
  void toggle();

  int getOption();

  bool isOn();
};

#endif
