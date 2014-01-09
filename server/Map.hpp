#ifndef MAP_HPP
#define MAP_HPP

#include <list>
#include <iostream>

class Map
{
public:
  Map(std::string fileName);
  std::pair<int,int> getTankPosition();
  std::string getData();

private:
  std::string data;
  std::list<std::pair<int,int> > tankPositions;

};

#endif
