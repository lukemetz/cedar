#pragma once
#include <string>
#include <exception>
#include <sstream>

namespace cedar
{
  class SpecException : public std::exception
  {
  public:
    SpecException(std::string error, std::string fileName, int lineNumber)
    {
      this->error = error;
      this->fileName = fileName;
      this->lineNumber = lineNumber;
    }

    std::string error;
    std::string fileName;
    int lineNumber;
  };
};

