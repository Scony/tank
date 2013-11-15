#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <iostream>

class Exception
{
  std::string message;
 public:
  Exception(std::string message);
  Exception();
  ~Exception();

  std::string toString();
};

#endif
