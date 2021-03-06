/* @file GTestSuite.h
   @brief Manager of all reverie tests
*/

#ifndef J_TEST_SUITE_H
#define J_TEST_SUITE_H

/////////////////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////////////////
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////////
// Begin namespace
/////////////////////////////////////////////////////////////////////////////////////////////

namespace joby {

class Test;
/////////////////////////////////////////////////////////////////////////////////////////////
// Class Definitions
/////////////////////////////////////////////////////////////////////////////////////////////

/// @class TestSuite
class TestSuite {
public:
    /// @name Static
    /// @{
    /// @}

    /// @name Constructors/Destructor
    /// @{

    TestSuite();
    ~TestSuite();

    /// @}

    /// @name Public methods
    /// @{

    /// @brief Add a test to perform to the list of tests
    void addTest(Test* test);

    /// @brief Run all of the tests in the suite
    void runTests() const;

    /// @}

protected:
    /// @name Protected Members
    /// @{

    std::vector<Test*> m_tests;

    /// @}

};



/////////////////////////////////////////////////////////////////////////////////////////////
// End namespace
/////////////////////////////////////////////////////////////////////////////////////////////
}


#endif