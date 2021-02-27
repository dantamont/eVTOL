#ifndef TEST_UNITS_H
#define TEST_UNITS_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../JTest.h"
#include <core/physics/JUnits.h>
#include <core/physics/JQuantity.h>

namespace joby{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tests
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class UnitsTest : public Test
{
public:

    UnitsTest(): Test(){}
    ~UnitsTest() {}

    /// @brief Perform unit tests for Timer class
    virtual void perform() {

        // Test a Quantity conversion
        bool integral = std::is_integral_v<TimeUnits>;
        Quantity<TimeUnits::kSeconds> secs(60);
        auto timeUnits = secs.units();
        double minutes = secs.to<TimeUnits::kMinutes>().value();
        assert_(minutes == 1.0);

        // Test a few unit conversions as a proof of concept
        // TODO: Test all possible combinations of units
        size_t numSeconds = Units::ConvertToSI<TimeUnits::kDays>(1);
        assert_(numSeconds == 86400);

        size_t numMinutes = Units::Convert<TimeUnits::kDays, TimeUnits::kMinutes>(1);
        assert_(numMinutes == 1440);

        size_t numMinutes2 = Units::Convert<TimeUnits::kSeconds, TimeUnits::kMinutes>(60);
        assert_(numMinutes2 == 1);

        size_t numDays = Units::Convert<TimeUnits::kMinutes, TimeUnits::kDays>(2880);
        assert_(numDays == 2);

        double numDaysd = Units::Convert<TimeUnits::kMinutes, TimeUnits::kDays>(2880.0);
        assert_(numDaysd == 2);

    }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End namespaces
}


#endif