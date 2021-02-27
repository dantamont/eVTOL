#include <iostream>

#include "GTestSuite.h"
#include "unit_tests/GTestDagNode.h"
#include "unit_tests/GTestEulerAngle.h"
#include "unit_tests/GTestMatrix.h"
#include "unit_tests/GTestParallelization.h"
#include "unit_tests/GTestProtocol.h"
#include "unit_tests/GTestQuaternion.h"
#include "unit_tests/GTestVector.h"

using namespace Gb;

int main(int argc, char* argv[]) {
    // Create tests
    TestSuite tests;
    tests.addTest(new DagNodeTest());
    tests.addTest(new EulerAnglesTest());
    tests.addTest(new MatrixTest());
    tests.addTest(new ParallelizationTest());
    tests.addTest(new ProtocolTest());
    tests.addTest(new QuaternionTest());
    tests.addTest(new VectorTest());

    // Run tests
    tests.runTests();

    return 0;
}