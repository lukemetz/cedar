#include "SpecFunctions.h"
#include "Spec.h"

namespace cedar
{
  void describe(std::string text, std::function<void()> closure)
  {
    auto parentSpec = currentSpec;
    auto spec = std::make_shared<Spec>(text, []{});
    parentSpec->addChild(spec);
    currentSpec = spec;
    closure();
    currentSpec = parentSpec;
  }

  void it(std::string text, std::function<void()> closure)
  {
    auto spec = std::make_shared<Spec>(text, closure);
    currentSpec->addChild(spec);
  }
}
