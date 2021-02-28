#ifndef J_PROCESS_H
#define J_PROCESS_H
/** @file JProcess.h 
    Abstract class for a process to be run in a process queue
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <memory>
#include <atomic>
#include <assert.h>
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
enum class ProcessState {
    kUninitialized = 0, // Created, but not running
    kRemoved, // Removed from the process list, but not destroyed, e.g. if running process is parented to another process
    kRunning, // Living processes
    kPaused, // Initialized, but paused
    // Dead processes
    kSucceeded, // Completed successfully
    kFailed, // Failed to complete
    kAborted // Aborted, may not have started
};

/// @class Process
class Process {
public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @name Static
    /// @{
    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Constructor/Destructor
    /// @{

    Process() {
        // Set the unique ID of the proocess
        // NOTE: In production code, I would also keep track of deleted process IDs,
        // and re-use them to ensure that I don't get overflow
        static std::atomic<size_t> processCount;
        m_id = processCount;
        processCount.fetch_add(1);
    }
    virtual ~Process() {}

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Properties
    /// @{

    /// @brief The unique ID of the process
    size_t id() const { return m_id; }

    /// @brief The order of the process
    int getSortingLayer() const { return m_sortingLayer; }
    void setSortingLayer(int layer) { m_sortingLayer = layer; }

    /// @brief The state of the process
    ProcessState getState(void) const { return m_state.load(); }
    void setState(const ProcessState& state) { m_state.store(state); }

    /// @brief Wrappers on process state to get current status
    inline bool isAlive(void) const { return (m_state == ProcessState::kRunning || m_state == ProcessState::kPaused); }
    inline bool isDead(void) const { return (m_state == ProcessState::kSucceeded || m_state == ProcessState::kFailed || m_state == ProcessState::kAborted); }
    inline bool isRemoved(void) const { return (m_state == ProcessState::kRemoved); }
    inline bool isPaused(void) const { return m_state == ProcessState::kPaused; }
    inline bool isAborted(void) const { return m_state == ProcessState::kAborted; }

    /// @brief Convert the process to a subclass
    template<typename T>
    T* as() {
        static_assert(std::is_base_of_v<Process, T>, "Error, can only convert to a process type");
        return dynamic_cast<T*>(this);
    }


    /// @}

    //-----------------------------------------------------------------------------------------------------------------
	/// @name Public Methods
	/// @{

    /// @brief Functions to be overriden by process subclasses as needed
    virtual void onInit() { m_state.store(ProcessState::kRunning); }
    virtual void onUpdate(double deltaMs) = 0;
    virtual void onFixedUpdate(double deltaMs) = 0;
    virtual void onSuccess() {}
    virtual void onFail() {}
    virtual void onAbort() {}

    /// @brief Run the process update loop
    /// @details Returns true if the process has died, else false
    bool runProcess(double sec);

    /// @brief Run the process fixed update loop
    /// @details Returns true if the process has died, else false
    bool runFixed(double sec);

    /// @brief Functions for ending the process.
    inline void succeed(void) {
        ProcessState state = getState();
        assert(state == ProcessState::kRunning || state == ProcessState::kPaused);
        setState(ProcessState::kSucceeded);
    }
    inline void fail(void) {
        ProcessState state = getState();
        assert(state == ProcessState::kRunning || state == ProcessState::kPaused);
        setState(ProcessState::kFailed);
    }
    inline void abort(void) {
        ProcessState state = getState();
        assert(state == ProcessState::kRunning || state == ProcessState::kPaused || m_state == ProcessState::kUninitialized);
        setState(ProcessState::kAborted);
    }

    /// @brief Pause the process
    inline void pause(void) {
        if (getState() == ProcessState::kRunning) {
            setState(ProcessState::kPaused);
        }
#ifdef DEBUG_MODE
        else {
            throw("Error, invalid state switch");
        }
#endif
    }

    /// @brief Resume the process
    inline void unPause(void) {
        if (getState() == ProcessState::kPaused){
            setState(ProcessState::kRunning);
        }
#ifdef DEBUG_MODE
        else {
            throw("Error, invalid state switch");
        }
#endif
    }

	/// @}

protected:

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Protected Methods
    /// @{

    /// @brief Check if the process is finished
    bool checkFinished();

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Members
    /// @{

    /// @brief Determines the priority of the process via the sorting order each frame,
    /// @details A lower value means a higher priority
    int m_sortingLayer;

    /// @brief The status of the process
    /// @details This needs to be atomic to avoid undefined behavior when querying
    std::atomic<ProcessState> m_state;

    /// @}

private:

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Members
    /// @{

    /// @brief the unique ID of the process
    size_t m_id;

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Static
    /// @{

    /// @}
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // end namespacing

#endif