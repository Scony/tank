#ifndef WRAPPER_BOX_HPP
#define WRAPPER_BOX_HPP

#include "Wrapper.hpp"

class WrapperBox
{
  Wrapper * wrapper;
public:
  WrapperBox(Wrapper * wrapper);
  ~WrapperBox();

  Wrapper * getWrapper();
};

#endif
