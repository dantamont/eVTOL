#include "GTestSuite.h"
#include "GTest.h"
#include <core/containers/GbString.h>

/////////////////////////////////////////////////////////////////////////////////////////////
// Begin namespace
/////////////////////////////////////////////////////////////////////////////////////////////

namespace Gb {


TestSuite::TestSuite()
{
}

TestSuite::~TestSuite()
{
    for (Test* test : m_tests) {
        delete test;
    }
}

void TestSuite::addTest(Test * test)
{
    m_tests.push_back(test);
}

void TestSuite::runTests() const
{
    for (Test* test : m_tests) {
        const char* testClassName = typeid(*test).name();
        try {
            test->perform();
            Logger::LogInfo(GString::Format("%s:: Test passed", testClassName).c_str());
        }
        catch (...) {
            Logger::LogError(GString::Format("Test failure in: %s", testClassName).c_str());
        }
    }
}



/////////////////////////////////////////////////////////////////////////////////////////////
// End namespace
/////////////////////////////////////////////////////////////////////////////////////////////
}
