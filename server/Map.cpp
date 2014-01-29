#include <fstream>
#include <cstdlib>

#include "Map.hpp"

using namespace std;

Map::Map(string fileName)
{
  system("./mapgen.out > medium.map");
  ifstream in(fileName.c_str());
  string line;
  data = "";
  while(getline(in,line))
    data += line + "\n";

  for(int i = 0; i < 10; i++)
    {
      int a = 5 * 32 * i + 16;
      int b = 5 * 32 * i + 16;
      tankPositions.push_back(pair<int,int>(a,b));
    }
}

pair<int,int> Map::getTankPosition()
{
  pair<int,int> re = tankPositions.front();
  tankPositions.pop_front();

  return re;
}

string Map::getData()
{
  return data;
}
