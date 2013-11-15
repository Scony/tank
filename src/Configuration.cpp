#include "Configuration.hpp"

using namespace std;

Configuration::Configuration()
{
  path = "./";
}

Configuration::Configuration(const Configuration& c)
{
}

Configuration& Configuration::operator=(const Configuration& c)
{
  return *this;
}

Configuration * Configuration::getInstance()
{
  static Configuration configuration;

  return &configuration;
}

void Configuration::setPath(string path)
{
  this->path = path.substr(0,path.length()-8);
}

string Configuration::getPath()
{
  return path;
}

int Configuration::getBig()
{
  return big;
}

int Configuration::getMedium()
{
  return medium;
}

int Configuration::getSmall()
{
  return small;
}

