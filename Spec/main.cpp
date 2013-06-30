#include "Cedar.h"
#include <iostream>

int main(int argc, char *argv[])
{
  std::cout << "Hello world" << std::endl;
  cedar::Reporter reporter;
  return cedar::runTests(reporter);
}
