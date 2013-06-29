#include "Headers/Spec.h"
#include "Headers/Reporter.h"

namespace cedar
{
  std::shared_ptr<Spec> currentSpec;
  
  Spec::Spec(std::string text, std::function<void()> closure)
    :text(text), closure(closure)
  {
  }

  Spec::~Spec()
  {
  }

  void Spec::addChild(std::shared_ptr<Spec> spec)
  {
    children.push_back(spec);
    spec->parent = this;
  }

  void Spec::load()
  {
    this->closure();
    for (std::shared_ptr<Spec> spec : children) {
      spec->load();
    }
  }

  void Spec::run(Reporter& reporter)
  {
    if (children.size() == 0) {
      try {
        closure();
        reporter.successTest();
      } catch (SpecException & e) {
        reporter.failTest(location(), e);
      }
    } else {
      for (std::shared_ptr<Spec> child : children) {
        child->run(reporter);
      }
    }
    if (nullptr == parent) {
      reporter.endTests();
    }
  }

  std::vector<std::string> Spec::location()
  {
    std::vector<std::string> ret;
    Spec * onSpec = this;
    while (nullptr != onSpec) {
      ret.insert(ret.begin(), onSpec->text);
      onSpec = onSpec->parent;
    }
    return ret;
  }

}
