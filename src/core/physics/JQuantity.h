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

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Public Methods
    /// @{

    //IType value() const { return m_value; }

    //template<typename ToUnits, ToUnits NewVal>
    //Quantity_impl<ToUnits, EnumVal> to() {
    //    // Compile-time check for compatible unit type
    //    static_assert(std::is_same_v<ToUnits, EnumType>, "Error, incompatible units");
    //    return Units::Convert<EnumVal, NewVal>(m_value);
    //}

    /// @}

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
    /// @name Constructor/Destructor
    /// @{

    Quantity(IType value) :
        m_impl(value) {

    }
    ~Quantity(){}

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Properties
    /// @{

    IType value() const { return m_impl.m_value; }
    decltype(EnumVal) units() const { return EnumVal; }

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
	/// @name Public Methods
	/// @{

    template<auto ToUnits>
    Quantity<ToUnits> to() {
        // Compile-time check for compatible unit type
        static_assert(std::is_same_v<decltype(ToUnits), decltype(EnumVal)>, "Error, incompatible units");
        return Units::Convert<EnumVal, ToUnits>(m_impl.m_value);
    }

	/// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Operators
    /// @{

    operator IType() const {
        return m_impl.m_value;
    }

    /// @}


protected:

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Members
    /// @{

    /// @brief The encapsulated implementation of a quantity, wrapped for cleaner syntax
    Quantity_impl<decltype(EnumVal), EnumVal, IType> m_impl;

    /// @}

};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // end namespacing

#endif