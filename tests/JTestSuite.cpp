#include "JTestSuite.h"
#include "JTest.h"
#include <typeinfo>

#include <core/diagnostics/JLogger.h>
#include <core/containers/JString.h>
/////////////////////////////////////////////////////////////////////////////////////////////
// Begin namespace
/////////////////////////////////////////////////////////////////////////////////////////////

namespace joby {


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
    Logger::LogInfo("Running tests");
    for (Test* test : m_tests) {
        const char* testClassName = typeid(*test).name();
        try {
            test->perform();
            Logger::LogInfo(JString::Format("%s:: Test passed", testClassName).c_str());
        }
        catch (...) {
            Logger::LogError(JString::Format("Test failure in: %s", testClassName).c_str());
        }
    }
}



/////////////////////////////////////////////////////////////////////////////////////////////
// End namespace
/////////////////////////////////////////////////////////////////////////////////////////////
}
