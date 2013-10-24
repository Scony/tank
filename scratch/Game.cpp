#include "Game.hpp"

Game::Game(int w, int h)
{
  buffer = create_bitmap(w,h);
  // add exception
}

Game::~Game()
{
  destroy_bitmap(buffer);
}

BITMAP * Game::getBuffer()
{
  return buffer;
}
