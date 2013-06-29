#include "Cedar.h"
#include "Matchers/CedarMatchers.h"

using namespace cedar;
using namespace cedar::matchers;

//extern std::shared_ptr<Spec> rootSpec;

SPEC_BEGIN(SpecContainerSpec)
  describe("construction", [] {
    describe("when there is no rootSpec", [&]{
      it("sets the root spec to a new spec with no text", []{
        //Save the current root spec
        std::shared_ptr<Spec> back = rootSpec;
        rootSpec = nullptr;

        SpecContainer specContainer("Spec Name", []{});
        auto resultRootSpec = rootSpec;
        //Reset the root spec so this test will work
        rootSpec = back;
        resultRootSpec should_not equal(nullptr);
      });

      it("adds a child spec to the root spec", []{
        //Save the current root spec
        std::shared_ptr<Spec> back = rootSpec;
        rootSpec = nullptr;

        SpecContainer specContainer("Spec Name", []{});
        auto resultRootSpec = rootSpec;
        //Reset the root spec so this test will work
        rootSpec = back;
        resultRootSpec->children.size() should equal(1);
      });

      it("runs the lambda from constructor with the new spec as currentSpec", []{
        //Save the current root spec
        std::shared_ptr<Spec> back = rootSpec;
        rootSpec = std::make_shared<Spec>("Root", []{});

        std::shared_ptr<Spec> currentSpecSave = nullptr;

        SpecContainer specContainer("Spec Name", [&]{
          currentSpecSave = currentSpec;
        });
        auto resultRootSpec = rootSpec;
        //Reset the root spec so this test will work
        rootSpec = back;

        resultRootSpec->children.size() should equal(1);
        resultRootSpec->children[0] should equal(currentSpecSave);
      });
    });
  });

SPEC_END
