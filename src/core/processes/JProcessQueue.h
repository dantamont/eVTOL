#ifndef J_PROCESS_QUEUE_H
#define J_PROCESS_QUEUE_H
/** @file JProcessQueue.h 
    Defines a queue for handling processes
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <thread>
#include <core/threading/JThreadPool.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Namespace Definitions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace joby {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Process;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class Definitions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @struct CompareBySortingLayer
/// @brief Struct containing a comparator for sorting processes list by sorting layer
struct CompareBySortingLayer {
    bool operator()(const std::shared_ptr<Process>& a, const std::shared_ptr<Process>& b) const;

    static CompareBySortingLayer s_compareBySortingLayer;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class ProcessQueue
class ProcessQueue {
public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @name Static Methods
    /// @{

    ProcessQueue(size_t threadCount);
    ~ProcessQueue();

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

    /// @brief Called on destruction, clears all processes
    void clearAllProcesses();

    /// @brief Refresh order of processes to reflect sorting layer changes
    void reorderProcesses();

    /// @brief Updates all attached processes
    void updateProcesses(unsigned long deltaMs);

    /// @brief Fixed-updates all attached processes
    void fixedUpdateProcesses(unsigned long deltaMs);

    /// @brief Attach a process to the process manager
    void attachProcess(const std::shared_ptr<Process>& process, bool initialize = false);

    /// @brief Aborts all processes
    void abortAllProcesses(bool immediate);

	/// @}

protected:
    //-----------------------------------------------------------------------------------------------------------------
    /// @name Methods
    /// @{

    /// @brief Abort a given process
    void abortProcess(const std::shared_ptr<Process>& process, bool immediate);

    /// @brief Delete the threaded process with the given ID from the queue
    void deleteThreadedProcess(size_t id);

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Members
    /// @{

    /// @brief Threadpool for managing threads for any asynchronous processes
    ThreadPool m_threadPool;

    /// @brief Mutex for threaded process vector
    std::mutex m_threadedProcessMutex;

    /// @brief Queue for temporarily staging processes to run
    /// @note Using shared pointers to avoid manual memory management
    std::vector<std::shared_ptr<Process>> m_processQueue;

    /// @brief All unthreaded processes, iterated over in simulation loop
    std::vector<std::shared_ptr<Process>> m_processes;

    /// @brief All asynchronous processes
    std::vector<std::shared_ptr<Process>> m_threadedProcesses;

    /// @}

};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // end namespacing

#endif