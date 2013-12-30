#ifndef GAME_HPP
#define GAME_HPP

#include <list>

#include "Tank.hpp"

#define GAME_SIZE 2

class Game
{
public:
  Game();
  void updateTank(int id, int x, int y, int rotation, int shoot);
  void deleteTank(int id);
  bool isOver();
  std::string getInitData(int id);
  std::string getData();
  int getId();

private:
  int gid;
  std::list<Tank> tanks;

private:
  static int gidc;

};

#endif
