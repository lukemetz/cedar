#include "Headers/testRunner.h"
#include "Headers/SpecContainer.h"
#include "Headers/Reporter.h"

int cedar::runTests(cedar::Reporter& r)
{
  cedar::rootSpec->run(r);
  return 1;
}
