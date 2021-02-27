#ifndef J_SCENE_H
#define J_SCENE_H
/** @file JScene.h 
    Defines a scene containing all of the entities required to simulate eVTOL operationns
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <vector>

#include <apps/eVTOL/entities/charger/JCharger.h>
#include <apps/eVTOL/entities/company/JCompany.h>
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
/// @class Scene
/// @brief Contains all entities required to simulate eVTOL operations
/// @note I have intentionally avoided storing aircraft instantiations within the Company
/// objects themselves, since vectorization of objects is more cache-friendly
class Scene {
public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @name Static Methods
    /// @{
    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Constructor/Destructor
    /// @{

    Scene();
    ~Scene();

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Properties
    /// @{
    /// @}

    //-----------------------------------------------------------------------------------------------------------------
	/// @name Public Methods
	/// @{

    /// @brief Add a company to the scene
    /// @param[in] The name of the company to be added
    /// @param[in] The eVTOL characteristics
    template<typename ...Args>
    Company& addCompany(Args&&... args) {
        return m_companies.emplace_back(std::forward<Args>(args)...);
    }

    /// @brief Set the number of chargers in the scene
    void setChargerCount(size_t count);

	/// @}

protected:

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Members
    /// @{

    /// @note If there were any need for polymorphic behavior, I would
    /// store pointers to these objects instead of value types, but it
    /// is more cache-friendly to store things this way

    /// @brief The companies in the scene
    std::vector<Company> m_companies;

    /// @brief The vehicles in the scene
    std::vector<Aircraft> m_aircraft;

    /// @brief The chargers in the scene
    std::vector<Charger> m_chargers;

    /// @}

};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // end namespacing

#endif