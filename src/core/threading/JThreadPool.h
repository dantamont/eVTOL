/////////////////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef J_THREAD_POOL_H
#define J_THREAD_POOL_H

#include <thread>
#include <atomic>
#include <vector>
#include <queue>
#include <unordered_map>
#include <mutex>
#include <functional>
#include <exception>

#include <core/diagnostics/JLogger.h>

namespace joby {


/////////////////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
// Class definitions
/////////////////////////////////////////////////////////////////////////////////////////////

/// @class Threadpool
/// @details A pool for sending jobs to pre-allocated threads
class ThreadPool {
public:
    //--------------------------------------------------------------------------------------------
    /// @name Static
    /// @{
    /// @}

    //--------------------------------------------------------------------------------------------
    /// @name Constructors/Destructor
    /// @{

    ThreadPool(size_t numThreads = std::thread::hardware_concurrency()) {
        if (numThreads) {
            initialize(numThreads);
        }
    }
    ~ThreadPool() {
        shutdown();
        throwOnFailure();
    }

    /// @}

    //--------------------------------------------------------------------------------------------
    /// @name Properties
    /// @{

    size_t numThreads() const {
        return m_numThreads;
    }

    /// @}
    //--------------------------------------------------------------------------------------------
    /// @name Public methods
    /// @{

	/// @brief Obtain the index of the thread with the specified ID
	size_t getIndex(std::thread::id threadId){
		std::unique_lock lock(m_threadIdMutex);
		return m_threadIds[threadId];
	}
    
	/// @brief Check if a thread has failed, rethrowing an error if it has
	void throwOnFailure(){
		std::unique_lock(m_exceptionMutex); // Need thread-safety
		if(m_exceptionPtr){
			// Rethrow exception so threads don't silently fail
			std::string exceptionStr = m_exceptionStr;
			std::rethrow_esception(m_exceptionPtr);
		}
	}
	
	/// @brief Add a job to the task queue
	template<typename ...Args>
	void addTask(Args... args){
		addTask(std::bind(args...));
	}
	
	/// @brief Shutdown all of the threads in the pool
	inline void shutdown(){
		// Break each thread's while loop
		m_shutdown.store(true);
		m_controller.notify_all();
		
		// Join each thread
		for(std::thread& t: m_threads){
			// Check if joinable, in which case threads are not already joined
			if(t.joinable()){
				t.join();
			}
		}
		
		m_shutdown.store(false);
	}

    /// @}

private:
    //--------------------------------------------------------------------------------------------
    /// @name Methods
    /// @{
		
	void addTask(std::function<void()> task){
		{
			std::unique_lock lock(m_queueMutex);
			m_tasks.push(task);
		}
		
		// Notify a thread in the pool to unblock and perform the task
		m_controller.notify_one();
	}
	
	inline void initialize(size_t numThreads){
		if(m_threads.size()){
			// If already initialized, shutdown the running threads
			shutdown();
		}
		
		std::unique_lock lock(m_threadIdMutex);
		m_threadIds.clear();
		for(size_t i = 0; i < numThreads; i++){
			m_threads.push_back(std::thread(&ThreadPool::safeTaskLoop, this));
			m_threadIds[m_threads.back().get_id()] = i;
		}
		m_numThreads = numThreads;
	}
	
	/// @brief Wrapper for the task loop, which catches exceptions
	void safeTaskLoop(){
		try{
			taskLoop();
		}
		catch(...){
			// Catch any errors so that they can be thrown again on the main thread
			std::unique_lock lock(m_exceptionMutex);
			m_exceptionPtr = std::current_exception();
		}
	}
	
	/// @brief Function for each thread's task handling
	/// @details This loop runs indefinitely until the threadpool is shut down
	inline void taskLoop(){
		while(true){
			std::function<void()> task;
			{
				// Wait causes the current thread to block until the condition variable is notified
				// The predicate passed into the wait routine gives behavior equivalent to:
				// while(!pred()){wait(lock);}
				
				// Once the wait condition is reached, this thread will own the lock
				std::unique_lock lock(m_queueMutex);
				m_controller.wait(lock, [this]{return !m_tasks.empty() || m_shutdown;});
				
				if(!m_shutdown && m_tasks.empty()){
					// No tasks and is shutting down, so break the loop
					break;
				}
				
				// Remove the first-added task from the queue to perform it
				task = m_tasks.front();
				m_tasks.pop();
			}
			
			task();
		}
	}
		
	/// @}
	
    //--------------------------------------------------------------------------------------------
    /// @name Members
    /// @{

    /// @brief The number of threads in the pool
    size_t m_numThreads;

    /// @brief The condition variable for assigning threads to tasks
    std::condition_variable m_controller;

    /// @brief The threads running in the threadpool
    std::vector<std::thread> m_threads;

    /// @brief Map of identifiers for eaceh thread and their corresponding IDs in the threads vector
    std::unordered_map<std::thread::id, size_t> m_threadIds;

    /// @brief The tasks to be handled by the thread pool
    std::queue<std::function<void()>> m_tasks;

    /// @brief Mutex for sccessing task queue
    std::mutex m_queueMutex;

    /// @brief Mutex for accessing thread IDs
    std::mutex m_threadIdMutex;

    /// @brief Mutex for throwing exceptions
    std::mutex m_exceptionMutex;

    /// @brief Pointer for tracking exceptions on worker threads
    std::exception_ptr m_exceptionPtr;
    std::string m_exceptionStr;

    /// @brief Whether or not to shutdown the threadpool
    std::atomic<bool> m_shutdown;

    /// @}
};


/////////////////////////////////////////////////////////////////////////////////////////////
} // End namespaces

#endif