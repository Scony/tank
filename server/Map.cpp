#include <fstream>
#include <sstream>

#include "Map.hpp"

using namespace std;

Map::Map(string fileName)
{
  ifstream in(fileName.c_str());
  stringstream ss;

  int n;
  int m;

  // map matrix
  in >> n >> m;
  ss << n << " " << m << endl;
  for(int i = 0; i < m; i++)
    {
      for(int j = 0; j < n; j++)
	{
	  int val;
	  in >> val;
	  ss << val;
	  if(j+1 < n)
	    ss << " ";
	}
      ss << endl;
    }

  // consumables list
  in >> n;
  ss << n << endl;
  for(int i = 0; i < n; i++)
    {
      int a;
      int b;
      int c;
      int d;
      in >> a >> b >> c >> d;
      ss << a << " " << b << " " << c << " " << d;
      if(i+1 < n)
	ss << endl;
    }

  // spots list
  in >> n;
  for(int i = 0; i < n; i++)
    {
      int a;
      int b;
      in >> a >> b;
      tankPositions.push_back(pair<int,int>(a,b));
    }

  data = ss.str();
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
