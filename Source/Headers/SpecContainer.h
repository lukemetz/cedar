#pragma once

#include "Spec.h"

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <functional>

namespace cedar
{
  extern std::shared_ptr<Spec> rootSpec;
  class SpecContainer
  {
  public:
    SpecContainer(std::string name, std::function<void()> closure);
  };
};
