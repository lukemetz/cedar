#include "Cedar.h"
#include "Matchers/CedarMatchers.h"

void failWithError(std::string expected, std::function<void()> closure)
{
  try {
    closure();
  } catch (cedar::SpecException & e) {
    e.error should cedar::matchers::equal(expected);
  }
}
