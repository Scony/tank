#include <fstream>

#include "PolicyManager.hpp"
#include "Exception.hpp"

using namespace std;

PolicyManager::PolicyManager(string fileName)
{
  ifstream in(fileName.c_str());
  if(!in)
    throw new Exception("Can not load " + fileName);

  in >> size;

  collisions = new bool * [size];
  overlaps = new bool * [size];
  for(int i = 0; i < size; i++)
    {
      collisions[i] = new bool[size];
      overlaps[i] = new bool[size];
    }

  for(int i = 0; i < size; i++)
    for(int j = 0; j < size; j++)
      {
	int tmp;
	in >> tmp;
	collisions[j][i] = tmp ? true : false;
      }

  for(int i = 0; i < size; i++)
    for(int j = 0; j < size; j++)
      {
	int tmp;
	in >> tmp;
	overlaps[j][i] = tmp ? true : false;
      }

  in.close();
}

PolicyManager::~PolicyManager()
{
  for(int i = 0; i < size; i++)
    delete collisions[i];
  delete collisions;
}

bool PolicyManager::checkCollisionability(int a, int b)
{
  if(0 <= a && a < size && 0 <= b && b < size)
    return a <= b ? collisions[a][b] : collisions[b][a];
  return true;
}

bool PolicyManager::checkOverlapability(int a, int b)
{
  if(0 <= a && a < size && 0 <= b && b < size)
    return overlaps[a][b];
  return false;
}
