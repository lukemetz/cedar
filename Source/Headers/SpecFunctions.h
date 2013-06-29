#pragma once

#include <string>
#include <functional>
#include <memory>

namespace cedar
{
  class SpecContainer;
  class Spec;
}

namespace cedar {

  extern std::shared_ptr<Spec> currentSpec;

  void describe(std::string text, std::function<void()> closure);
  void it(std::string text, std::function<void()> closure);
};

#define SPEC_BEGIN(name) \
cedar::SpecContainer name(#name, [&] {

#define SPEC_END                                  \
});
