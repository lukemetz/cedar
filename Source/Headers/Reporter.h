#pragma once
#include "Spec.h"
#include <exception>
#include "SpecException.h"

namespace cedar
{

  class Reporter
  {
  public:
    virtual void successTest()
    {
      successTests += 1;
      std::cout << ".";
    }

    virtual void failTest(std::vector<std::string> location, SpecException &e)
    {
      failTests += 1;
      std::cout << "F";
      failureMessages.push_back(formatFailMessage(location, e));
    }

    virtual void endTests()
    {
      std::cout << std::endl << successTests << " Passed "
        << failTests << " Failed" <<std::endl;
      for (auto message : failureMessages) {
        std::cout << message;
      }
    }

    std::string formatFailMessage(std::vector<std::string> location, SpecException &e)
    {
      std::stringstream stream;
      stream << e.fileName << ":" << e.lineNumber << " ";
      auto it = location.begin();
      for (; it != location.end()-1; it++) {
        stream << *it<< ">";
      }
      stream << *it << "\n";
      stream << "\t" << e.error << "\n";
      return stream.str();
    }

  private:
    std::vector<std::string> failureMessages;
    int successTests = 0;
    int failTests = 0;
  };
};
