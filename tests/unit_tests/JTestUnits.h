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

        // Test a few unit conversions as a proof of concept
        // TODO: Test all possible combinations of units
        size_t numSeconds = Units::ConvertToSI<TimeUnits::kDays>(1);
        assert_(numSeconds == 86400);

        size_t numMinutes = Units::Convert<TimeUnits::kDays, TimeUnits::kMinutes>(1);
        assert_(numMinutes == 1440);

        //size_t numMinutes1 = Units::Convert_impl<TimeUnits, TimeUnits::kSeconds, TimeUnits::kMinutes>(60);
        //assert_(numMinutes1== 1);

        //size_t numMinutes1 = Units::Convert<TimeUnits::kSeconds, AngularUnits::kDegrees>(60);

        size_t numMinutes2 = Units::Convert<TimeUnits::kSeconds, TimeUnits::kMinutes>(60);
        assert_(numMinutes2 == 1);

        size_t numDays = Units::Convert<TimeUnits::kMinutes, TimeUnits::kDays>(2880);
        assert_(numDays == 2);

        double numDaysd = Units::Convert<TimeUnits::kMinutes, TimeUnits::kDays>(2880.0);
        assert_(numDaysd == 2);

        double rads = 1.0;
        double degs = Units::Convert<AngularUnits::kRadians, AngularUnits::kDegrees>(rads);
        assert_(approxEqual(degs, 180 / 3.14159265358979323846));


        double meters = 100.0;
        bool same = std::is_same_v<DistanceUnits, AngularUnits>;
        assert_(!same);
        double kmeters = Units::Convert<DistanceUnits::kMeters, DistanceUnits::kKilometers>(meters);
        assert_(approxEqual(kmeters, 0.1));


        // Test a Quantity conversion
        //Quantity_impl<TimeUnits, TimeUnits::kSeconds> secsi(60);
        //auto minutesi = secsi.to<TimeUnits, TimeUnits::kMinutes>();
        //assert_(minutesi.value() == 1.0);

        Quantity<TimeUnits::kSeconds> secs(60);
        auto timeUnits = secs.units();
        auto minutes = secs.to<TimeUnits::kMinutes>();
        assert_(minutes.value() == 1.0);


    }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End namespaces
}


#endif