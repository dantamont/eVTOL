/////////////////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef J_THREADED_PROCESS_H
#define J_THREADED_PROCESS_H

// std
#include <exception>
#include <stdexcept>
#include <mutex>

// Internal
#include "JProcess.h"

namespace joby {
/////////////////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
// Typedefs
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
// Class definitions
/////////////////////////////////////////////////////////////////////////////////////////////

/// @class Process
/// @brief Represents a thread-friendly process
class ThreadedProcess: public Process {
public:
    //--------------------------------------------------------------------------------------------
    /// @name Static
    /// @{
    /// @}

	//--------------------------------------------------------------------------------------------
	/// @name Constructors/Destructor
	/// @{
    ThreadedProcess();
	virtual ~ThreadedProcess();

	/// @}

    //--------------------------------------------------------------------------------------------
    /// @name Properties
    /// @{

    std::mutex& exceptionMutex() { return m_exceptionLock; }
    const std::exception_ptr& exception() const { return m_exceptionPtr; }

    /// @}

	//--------------------------------------------------------------------------------------------
	/// @name Public Methods
	/// @{

    /// @brief Functions to be overriden by process subclasses as needed
    virtual void onInit() override{ m_state = ProcessState::kRunning; }
    virtual void onUpdate(double deltaMs) { deltaMs; }
    virtual void onSuccess() override;
    virtual void onFail() override { }
    virtual void onAbort() override{}

    /// @brief Required override for QRunnable for threaded process
    virtual void run();
	
    /// @}

protected:
    //--------------------------------------------------------------------------------------------
    /// @name Friends
    /// @{

    friend class ProcessManager;

    /// @}

    //--------------------------------------------------------------------------------------------
    /// @name Protected Methods
    /// @{
    /// @}

    //--------------------------------------------------------------------------------------------
    /// @name Protected Members
    /// @{

    mutable std::mutex m_exceptionLock;
    std::exception_ptr m_exceptionPtr = nullptr;

    /// @brief Time from the previous run of this process
    /// @details This needs to be cached locally, or
    double m_previousElapsedTime;

    /// @}
};

/////////////////////////////////////////////////////////////////////////////////////////////
} // End namespaces

#endif