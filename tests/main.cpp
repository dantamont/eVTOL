/*
  @file main.cpp
  @author Dante tufano
  @date 2/26/2021
  @brief File driving tests for the eVTOL application

  This project is meant to be used for unit and integration testing
  @see https://www.jobyaviation.com/
 */

#include <iostream>

#include "JTestSuite.h"
#include "unit_tests/JTestTimer.h"

using namespace joby;

int main(int argc, char* argv[]) {
    // Create tests
    TestSuite tests;
    tests.addTest(new TimerTest());

    // Run tests
    tests.runTests();

    // Wait until user closes window
    std::cout << "Press ENTER to close the window.";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return 0;
}
