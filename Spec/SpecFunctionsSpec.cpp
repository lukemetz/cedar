#include "Cedar.h"
#include "Matchers/CedarMatchers.h"

using namespace cedar;
using namespace cedar::matchers;

SPEC_BEGIN(SpecFunctionsSpec)
  describe("describe", [] {
    it("creates a new spec with text and adds it to the currentSpec", [] {
      auto oldCurrent = currentSpec;
      currentSpec = std::make_shared<Spec>("New Base", nullptr);
      auto closure = [&]{};
      describe("This test spec", closure);
      currentSpec->children.size() should equal(1);
      currentSpec->children[0]->text should equal("This test spec");

      currentSpec = oldCurrent;
    });

    it("runs the closure with the currentSpec set to itself", [] {
      auto oldCurrent = currentSpec;
      currentSpec = std::make_shared<Spec>("New Base", nullptr);

      std::shared_ptr<Spec> stashSpec;
      auto closure = [&] {
        stashSpec = currentSpec;
      };

      describe("This test spec", closure);
      stashSpec should equal(currentSpec->children[0]);

      currentSpec = oldCurrent;
    });

    it("resets the current spec when finished", [] {
      auto oldCurrent = currentSpec;
      currentSpec = std::make_shared<Spec>("New Base", nullptr);
      auto backup = currentSpec;
      describe("This test spec", []{});
      backup should equal(currentSpec);

      currentSpec = oldCurrent;
    });
  });

  describe("it", [] {
    it("creates a new spec with text and closure and adds it to the currentSpec", [] {
      auto oldCurrent = currentSpec;
      currentSpec = std::make_shared<Spec>("New Base", nullptr);
      bool a;
      auto closure = [&]{a=true;};
      it("do this", closure);
      currentSpec->children.size() should equal(1);
      currentSpec->children[0]->text should equal("do this");
      a = false;
      currentSpec->children[0]->closure();
      a should equal(true);

      currentSpec = oldCurrent;
    });
  });

  describe("SPEC_BEGIN/SPEC_END", []{
    it("should create a SpecContainer the token equal to the name", []{
      auto oldCurrent = currentSpec;
      currentSpec = std::make_shared<Spec>("New Base", nullptr);
      SPEC_BEGIN(macro);
      SPEC_END;

      &macro should_not equal(nullptr);

      currentSpec = oldCurrent;
    });
  });
SPEC_END
