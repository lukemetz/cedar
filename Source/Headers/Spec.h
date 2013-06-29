#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <functional>
namespace cedar
{
  class Reporter;
}

namespace cedar
{
  class Spec
  {
  public:
    Spec(std::string text, std::function<void()> closure);
    ~Spec();
    virtual void addChild(std::shared_ptr<Spec> spec);

    virtual void run(Reporter& reporter);
    virtual void load();
    virtual std::vector<std::string> location();

  //private:
    std::string text;
    std::vector<std::shared_ptr<Spec>> children;
    std::function<void()> closure = []{std::cout << "error\n";};
    Spec * parent = nullptr;
  };
}
