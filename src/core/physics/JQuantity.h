#ifndef J_QUANTITY_H
#define J_QUANTITY_H
/** @file JQuantity.h 
    Defines a quantity, consisting of a value and a base unit
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "JUnits.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Namespace Definitions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace joby {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<auto EnumVal, typename IType> class Quantity;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class Definitions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class Quantity_impl
/// @brief The implementation of the Quantity class, to be encapsulated by the Quantity class itself
/// @details This internal class exists to to enforce the Enum class type
template<typename EnumType, EnumType EnumVal, typename IType = double>
class Quantity_impl {
public:


    //-----------------------------------------------------------------------------------------------------------------
    /// @name Constructor/Destructor
    /// @{

    Quantity_impl(IType value) :
        m_value(value) {
    }
    ~Quantity_impl() {

    }

    /// @};

private:
    /// @brief Allow access via Quantity class
    friend class Quantity<EnumVal, IType>;

    IType m_value;
};

/// @class Quantity
/// @brief A quantity, consisting of a value and units
/// @details This templated implementation introduces no memory overhead, and provides
/// a framework for convenient unit conversions
template<auto EnumVal, typename IType = double>
class Quantity {
public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @name Static Methods
    /// @{
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
    /// @name Members
    /// @{

    /// @}

};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // end namespacing

#endif