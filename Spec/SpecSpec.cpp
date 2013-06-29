#include "Cedar.h"
#include "Matchers/CedarMatchers.h"

using namespace cedar;
using namespace cedar::matchers;

SPEC_BEGIN(SpecSpec)
  describe("location", [] {
    describe("with no parent", [] {
      it("has one location equal to the constructor text", []{;
        Spec spec("This text", []{});
        spec.location().size() should equal(1);
        spec.location()[0] should equal("This text");
      });

      it("the vector should list text from parent to child", []{
        Spec spec("The parent", []{});
        auto child = std::make_shared<Spec>("The child", []{});
        spec.addChild(child);
        child->location().size() should equal(2);
        child->location()[0] should equal("The parent");
        child->location()[1] should equal("The child");
      });
    });
  });

  describe("load", []{
    it("runs anonymous from the constructor and in its children", []{
      bool a=false, b=false, c=false;
      auto specA = std::make_shared<Spec>("", [&]{a = true;});
      auto specB = std::make_shared<Spec>("", [&]{b = true;});
      auto specC = std::make_shared<Spec>("", [&]{c = true;});
      specA->addChild(specB);
      specB->addChild(specC);

      specA->load();

      a should equal(true);
      b should equal(true);
      c should equal(true);
    });
  });

  describe("run", []{
    describe("when it has children", [] {
      class ReporterMock : public Reporter
      {
        public:
          virtual void successTest() {success += 1;}
          virtual void failTest(std::vector<std::string> location, SpecException & e)
          {
            fail += 1;
            this->location = location;
            lineNumber = e.lineNumber;
            fileName = e.fileName;
          }
          virtual void endTests()
          {
            end = true;
          }
          int success = 0;
          int fail = 0;
          bool end = false;

          std::vector<std::string> location;
          std::string fileName;
          int lineNumber = 0;
      };

      it("runs closures on leaf tests", [&]{
        bool c = false;
        bool d = false;

        auto specA = std::make_shared<Spec>("", nullptr);
        auto specB = std::make_shared<Spec>("", nullptr);
        auto specC = std::make_shared<Spec>("", [&]{c = true;});
        auto specD = std::make_shared<Spec>("", [&]{d = true;});
        specA->addChild(specB);
        specA->addChild(specD);
        specB->addChild(specC);

        ReporterMock reporter;
        specA->run(reporter);

        c should equal(true);
        d should equal(true);
      });

      it("calls successTest on Reporter for successful test", [] {
        auto specBase = std::make_shared<Spec>("", [&]{
          1 should equal(1);
        });
        ReporterMock reporter;
        specBase->run(reporter);

        reporter.success should equal(1);
        reporter.fail should equal(0);
      });

      it("calls failTest with location on Reporter for a failing test", [] {
        auto specBase = std::make_shared<Spec>("testSpec", [&]{
          1 should equal(2);
        });
        ReporterMock reporter;
        specBase->run(reporter);

        reporter.success should equal(0);
        reporter.fail should equal(1);
        reporter.location.size() should equal(1);
        reporter.location[0] should equal("testSpec");
      });

      it("calls failTest on Reporter with valid exception for a failing test", [] {
        int lineNumberHelper = 0;
        auto specBase = std::make_shared<Spec>("", [&]{
          lineNumberHelper = __LINE__ + 1;
          1 should equal(2);
        });
        ReporterMock reporter;
        specBase->run(reporter);

        reporter.success should equal(0);
        reporter.fail should equal(1);

        reporter.fileName should equal(__FILE__);
        reporter.lineNumber should equal(lineNumberHelper);
      });

      it("calls endTests when finished", [] {
        auto specBase = std::make_shared<Spec>("", [&]{
          1 should equal(1);
        });
        ReporterMock reporter;
        reporter.end = false;
        specBase->run(reporter);

        reporter.end should equal(true);
      });
    });
  });
SPEC_END
