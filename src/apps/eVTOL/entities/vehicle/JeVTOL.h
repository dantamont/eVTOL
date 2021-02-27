#ifndef J_EVTOL_H
#define J_EVTOL_H
/** @file JeVTOL.h 
    Defines an eVTOL vehicle
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
/// @class Aircraft
/// @brief Defines an eVTOL aircraft
/// @note In production code, I would likely create an abstract class representing a generic
/// aircraft, or even a vehicle. However, since this problem only assumes one type of vehicle,
/// I didn't bother
/// @note I have not defined a copy constructor or assignment operator, since this
/// class is intentionally trivially copyable
class Aircraft {
public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @name Static Methods
    /// @{
    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Constructor/Destructor
    /// @{

    Aircraft(double cruiseSpeed, double batteryCapacity, double chargeTime, double energyUse, size_t maxPassengerCount, double failureRate);
    ~Aircraft();

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
    /// @name Members
    /// @{

    /// @note If memory usage was an optimization priority over precision, I would
    /// use floats instead of doubles

    /// @brief Cruise speed in mph
    double m_cruiseSpeed;

    /// @brief Battery capacity in kWh
    double m_batteryCapacity;

    /// @brief Time to charge in hours
    double m_chargeTime;

    /// @brief Energy use at cruise (kWh/mile)
    double m_energyUse;

    /// @brief Allowed passenger count of the vehicle
    size_t m_maxPassengerCount;

    /// @brief Propability of fault per hour
    double m_failureRate;

    /// @}

private:

    /// @brief The unique ID corresponding to the company that created the eVTOL
    size_t m_companyId;

    /// @brief The unique ID corresponding to this eVTOL
    size_t m_id;


};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // end namespacing

#endif