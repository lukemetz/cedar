
#include "Cedar.h"
#include "Matchers/CedarMatchers.h"

#include "failWithError.h"

using namespace cedar;
using namespace cedar::matchers;

SPEC_BEGIN(EqualSpec)
  describe("when the actual value is a built-in type", []{
    describe("and the expected value is the same built-in type", [&]{
      describe("and the values are equal", [&]{
        describe("positive match", [&]{
          it("should pass", [&]{
            int actualValue = 1;
            int expectedValue = 1;
            actualValue should equal(expectedValue);
          });
        });
      });

      describe("negative match", []{
        it("should fail with a sensible failure message", []{
          int actualValue = 1;
          int expectedValue = 1;
          failWithError("Expected <1> to not equal <1>", [&] {
            actualValue should_not equal(expectedValue);
          });
        });
      });
    });

    describe("and the values are not equal", [] {
      describe("positive match", [] {
        it("should fail with a sensible failure message", [] {
          int actualValue = 1;
          int expectedValue = 147;
          failWithError("Expected <1> to equal <147>", [&] {
            actualValue should equal(expectedValue);
          });
        });
      });

      describe("negative match", [] {
        it("should pass", [] {
          int actualValue = 1;
          int expectedValue = 147;
          actualValue should_not equal(expectedValue);
        });
      });
    });

    describe("and the expected value is a different, but comparable, built-in type", []{
      describe("and the values are equal", [] {
        describe("positive match", [] {
          it("should pass", [] {
            int actualValue = 1;
            float expectedValue = 1.0f;
            actualValue should equal(expectedValue);
          });
        });

        describe("negative match", [] {
          it("should fail with a sensible failure message", [] {
            int actualValue = 1;
            float expectedValue = 1.0f;
            failWithError("Expected <1> to not equal <1>", [&] {
              actualValue should equal(expectedValue);
            });
          });
        });
      });

      describe("and the values are not equal", [] {
        describe("positive match", [] {
          it("should fail with a sensible failure message", [] {
            int actualValue = 1;
            float expectedValue = 0.87f;
            failWithError("Expected <1> to equal <0.87>", [&] {
              actualValue should equal(expectedValue);
            });
          });
        });

        describe("negative match", [] {
          it("should pass",[] { 
            int actualValue = 1;
            float expectedValue = 0.87f;
            actualValue should_not equal(expectedValue);
          });
        });
      });
    });
  });
SPEC_END
