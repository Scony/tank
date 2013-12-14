#include "WrapperBox.hpp"

WrapperBox::WrapperBox(Wrapper * wrapper)
{
  this->wrapper = wrapper;
}

WrapperBox::~WrapperBox()
{
}

Wrapper * WrapperBox::getWrapper()
{
  return wrapper;
}
