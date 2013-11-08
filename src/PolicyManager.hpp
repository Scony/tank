#ifndef POLICY_MANAGER_HPP
#define POLICY_MANAGER_HPP

#include <iostream>

class PolicyManager
{
  int size;
  bool ** collisions;
public:
  PolicyManager(std::string fileName);
  ~PolicyManager();

  bool checkCollisionability(int a, int b);
};

#endif
