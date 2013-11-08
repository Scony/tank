#ifndef POLICY_MANAGER_HPP
#define POLICY_MANAGER_HPP

#include <iostream>

class PolicyManager
{
  int size;
  bool ** collisions;
  bool ** overlaps;
public:
  PolicyManager(std::string fileName);
  ~PolicyManager();

  bool checkCollisionability(int a, int b);
  bool checkOverlapability(int a, int b);
};

#endif
