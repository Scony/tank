#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <iostream>

class Configuration
{
  std::string path;
  int big;
  int medium;
  int small;

  Configuration();
  Configuration(const Configuration& c);
  Configuration& operator=(const Configuration& c);
public:
  static Configuration * getInstance();

  void setPath(std::string path);
  std::string getPath();
  int getBig();
  int getMedium();
  int getSmall();
};

#endif
