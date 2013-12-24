#ifndef GAME_HPP
#define GAME_HPP

// shoot flag should be incremental to be sure everybody received shoot info

#include <list>

#include "Tank.hpp"

class Game
{
public:
  Game(int gid);
  ~Game();
  void updateTank(Tank tank);
  void deleteTank(Tank tank);
  bool isOver();
  std::string toString();

private:
  int gid;
  std::list<Tank> tanks;

#endif
