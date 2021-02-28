#ifndef J_SIMULATOR_H
#define J_SIMULATOR_H
/** @file JSimulator 

    File defining a simulation loop with event processing and time-stepping
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <functional>
#include <core/processes/JProcessQueue.h>

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
/// @class Simulator
class Simulator {
public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @name Static Methods
    /// @{
    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Constructor/Destructor
    /// @{

    Simulator(size_t numHelperThreads = std::thread::hardware_concurrency() / 2.0);
    ~Simulator();

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Properties
    /// @{
    /// @}

    //-----------------------------------------------------------------------------------------------------------------
	/// @name Public Methods
	/// @{

    /// @brief Perform a simulation
    /// @param[in] pred the predicate, which takes the total elapsed simulation time as an argument, and will 
    ///            terminate the simulation when pred(simulationTime) returns false
    /// @param[in] timeStepSec The fixed time-step, in seconds
    /// @note In production code, I may have logic in the simulation loop that is not physics-bound, and
    /// does not need to be run at a fixed time step
    void simulate(std::function<bool(double)> pred, const double timeStepSec);

	/// @}

protected:

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Members
    /// @{

    /// @brief Handles processes
    ProcessQueue m_processQueue;

    /// @}

};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // end namespacing

#endif