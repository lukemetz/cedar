#include "Headers/SpecContainer.h"
#include "SpecFunctions.h"
#include <string>

namespace cedar
{
  std::shared_ptr<Spec> rootSpec = nullptr;

  SpecContainer::SpecContainer(std::string name, std::function<void()> closure)
  {
    if (nullptr == rootSpec) {
      rootSpec = std::make_shared<Spec>("Root", [&]{});
      currentSpec = rootSpec;
    }
    std::shared_ptr<Spec> pointer = std::make_shared<Spec>(name, closure);
    rootSpec->addChild(pointer);

    currentSpec = pointer;
    closure();
    currentSpec = rootSpec;
  };
}
