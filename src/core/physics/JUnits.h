#ifndef J_UNITS_H
#define J_UNITS_H
/** @file JUnits.h 
    Defines a class representing a set of units
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <array>
#include <type_traits>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Namespace Definitions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace joby {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class Definitions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum class AngularUnits {
    kRadians = 0,
    kDegrees,
    COUNT
};

enum class DistanceUnits {
    kMeters=0,
    kKilometers,
    kCentimeters,
    kInches,
    kFeet,
    kMiles,
    COUNT
};

enum class TimeUnits {
    kSeconds = 0,
    kMinutes,
    kHours,
    kDays,
    kWeeks,
    kJulianYears,
    COUNT
};

enum class MassUnits {
    kKilograms = 0,
    kPounds,
    COUNT
};

/// @class Units
/// @brief Class containing helper methods unit conversions
class Units {
public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @name Static Methods
    /// @{

    template<auto From, auto To, typename T>
    static T Convert(T v) {
        return Convert_impl<decltype(From), From, To>(v);
    }

    template<auto From, typename T>
    static T ConvertToSI(T v) {
        return ConvertToSI_impl<decltype(From), From>(v);
    }

    template<auto To, typename T>
    static T ConvertFromSI(T v) {
        return ConvertFromSI_impl<decltype(To), To>(v);
    }

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Constructor/Destructor
    /// @{

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Properties
    /// @{
    /// @}

    //-----------------------------------------------------------------------------------------------------------------
	/// @name Public Methods
	/// @{

	/// @}

protected:

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Methods
    /// @{

    template<typename EnumType, EnumType From, EnumType To, typename T>
    static T Convert_impl(T v) {
        if constexpr (To == From) {
            // No conversion required
            return v;
        }
        else if constexpr (To == EnumType(0)) {
            // Converting to SI units
            return ConvertToSI_impl<EnumType, From>(v);
        }
        else {
            // Convert to SI, and then from SI to the final output
            return ConvertToSI_impl<EnumType, From>(v) * ConvertFromSI_impl<EnumType, To>(T(1.0));
        }
    }
    

    template<typename EnumType, EnumType From, typename T>
    static T ConvertToSI_impl(T v) {
        if constexpr (From == EnumType(0)) {
            // Converting from SI type to SI
            return v;
        }
        else {
            if constexpr (std::is_same_v<EnumType, AngularUnits>) {
                constexpr double factor = s_angularConversionsToSI[(size_t)From];
                return T(v * factor);
            }
            else if constexpr (std::is_same_v<EnumType, DistanceUnits>) {
                constexpr double factor = s_distanceConversionsToSI[(size_t)From];
                return T(v * factor);
            }
            else if constexpr (std::is_same_v<EnumType, TimeUnits>) {
                constexpr double factor = s_timeConversionsToSI[(size_t)From];
                return T(v * factor);
            }
            else if constexpr (std::is_same_v<EnumType, MassUnits>) {
                constexpr double factor = s_massConversionsToSI[(size_t)From];
                return T(v * factor);
            }
            else {
                throw("Unrecognized enum type");
            }
        }
    }

    template<typename EnumType, EnumType To, typename T>
    static T ConvertFromSI_impl(T v) {
        if constexpr (To == EnumType(0)) {
            // Converting from SI type to SI
            return v;
        }
        else {
            if constexpr (std::is_same_v<EnumType, AngularUnits>) {
                constexpr double factor = 1.0 / s_angularConversionsToSI[(size_t)To];
                return T(v * factor);
            }
            else if constexpr (std::is_same_v<EnumType, DistanceUnits>) {
                constexpr double factor = 1.0 / s_distanceConversionsToSI[(size_t)To];
                return T(v * factor);
            }
            else if constexpr (std::is_same_v<EnumType, TimeUnits>) {
                constexpr double factor = 1.0 / s_timeConversionsToSI[(size_t)To];
                return T(v * factor);
            }
            else if constexpr (std::is_same_v<EnumType, MassUnits>) {
                constexpr double factor = 1.0 / s_massConversionsToSI[(size_t)To];
                return T(v * factor);
            }
            else {
                throw("Unrecognized enum type");
            }
        }
    }

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Members
    /// @{

    static constexpr std::array<double, (size_t)AngularUnits::COUNT> s_angularConversionsToSI
    {
        1.0, // Radians to radians
        3.141592653589793238462643383279 /180.0 // Degrees to radians
    };

    static constexpr std::array<double, (size_t)DistanceUnits::COUNT> s_distanceConversionsToSI
    {
        1.0, // Meters to meters
        1000, // Kilometers to meters
        0.01, // Centimeters to meters
        0.0254, // Inches to meters
        0.3048, // Feet to meters
        1609.344 // Miles to meters
    };

    static constexpr std::array<double, (size_t)TimeUnits::COUNT> s_timeConversionsToSI
    {
        1.0, // Seconds to seconds
        60.0, // Minutes to seconds
        3600.0, // Hours to seconds
        24.0 * 3600.0, // Days to seconds
        7 * 24.0 * 3600.0, // Weeks to seconds
        365.25 * 24.0 * 3600.0 // Julian years to seconds
    };

    static constexpr std::array<double, (size_t)MassUnits::COUNT> s_massConversionsToSI
    {
        1.0, // kg to kg
        0.45359237 // pounds to kg
    };

    /// @}

};

/// @brief Define aliases for commonly used conversion functions
constexpr auto RadToDeg = Units::Convert<AngularUnits::kRadians, AngularUnits::kDegrees, double>;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // end namespacing

#endif