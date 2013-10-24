#include "Exception.hpp"

using namespace std;

Exception::Exception(string message)
{
  this->message = message;
}

Exception::Exception()
{
  message = "Exception";
}

Exception::~Exception()
{
}

string Exception::toString()
{
  return message;
}
