#ifndef J_COMPANY
#define J_COMPANY
/** @file JCompany.h 
    Defines a class representing a company, specifically an eVTOL vehicle company
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <apps/eVTOL/entities/vehicle/JeVTOL.h>

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
/// @class Company
/// @brief Defines an eVTOL manufacturer
/// @note I decided that this class was a nice way to have a factory generator of specifically-configured
/// eVTOL vehicles. I don't generally create subclasses if only the values of members
/// are changing, so this is an alternative way of instantiating distinct vehicle types.

class Company {
public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @name Static Methods
    /// @{
    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Constructor/Destructor
    /// @{

    Company(const std::string& name, const Aircraft& specification);
    ~Company();

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Properties
    /// @{

    const Aircraft& aircraftSpec() const { return m_aircraftSpec; }
    void setAircraftSpec(const Aircraft& aircraft) { m_aircraftSpec = aircraft; }

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
	/// @name Public Methods
	/// @{

	/// @}

protected:

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Members
    /// @{

    /// @brief The company name
    std::string m_name;

    /// @brief The aircraft as designed by this company
    /// @details This aircraft acts as a blueprint for all aircrafts instantiated by the company
    Aircraft m_aircraftSpec;

    /// @}

};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // end namespacing

#endif