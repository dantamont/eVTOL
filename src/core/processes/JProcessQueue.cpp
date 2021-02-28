#include "JProcessQueue.h"
#include "JProcess.h"
#include "JThreadedProcess.h"

namespace joby {
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sort layer comparator
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CompareBySortingLayer::operator()(const std::shared_ptr<Process>& a, const std::shared_ptr<Process>& b) const
{
    return a->getSortingLayer() < b->getSortingLayer();
}
CompareBySortingLayer CompareBySortingLayer::s_compareBySortingLayer = CompareBySortingLayer();


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Process Queue
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ProcessQueue::ProcessQueue(size_t threadCount):
    m_threadPool(threadCount? threadCount: 1) // Ensure at least one helper thread
{
}

ProcessQueue::~ProcessQueue()
{
}

void ProcessQueue::abortProcess(const std::shared_ptr<Process>& process, bool immediate)
{
    // Don't want to abort if already dead
    if (process->isAlive())
    {
        // Set the processes's state
        process->setState(ProcessState::kAborted);
        if (immediate)
        {
            // Immediately abort, rather than waiting for cleanup
            process->onAbort();

            // Remove from process set if not an asynchronous process
            if (ThreadedProcess* tp = process->as<ThreadedProcess>()) {
                // Throw any exceptions
                const std::exception_ptr& ex = tp->exception();
                if (ex) {
                    std::rethrow_exception(ex);
                }

                // Remove from threaded process list if threaded
                // Mutex should already be locked
                //QMutexLocker locker(&m_threadedProcessMutex);
                std::vector<std::shared_ptr<Process>>::const_iterator titer = std::find_if(m_threadedProcesses.begin(),
                    m_threadedProcesses.end(),
                    [&](std::shared_ptr<Process> p) {
                        return p->id() == process->id();
                    });
                if (titer != m_threadedProcesses.end()) {
                    m_threadedProcesses.erase(titer);
                }
            }
            else {
                std::vector<std::shared_ptr<Process>>::const_iterator iter = std::find_if(m_processes.begin(),
                    m_processes.end(),
                    [&](std::shared_ptr<Process> p) {
                        return p->id() == process->id();
                    });
                if (iter != m_processes.end()) {
                    m_processes.erase(iter);
                    return;
                }
            }
        }
    }
}

void ProcessQueue::deleteThreadedProcess(size_t id)
{
    auto iter = std::find_if(m_threadedProcesses.begin(), m_threadedProcesses.end(),
        [&](const std::shared_ptr<Process>& process) {
            if (!process) {
                return true;
            }
            else {
                return process->id() == id;
            }
        });
    if (iter != m_threadedProcesses.end()) {
        m_threadedProcesses.erase(iter);
    }
    else {
#ifdef DEBUG_MODE
        Logger::LogWarning("Warning, did not find threaded process to delete");
#endif
    }
}

void ProcessQueue::clearAllProcesses()
{
    // Abort all processes
    abortAllProcesses(true);

    // Clear process queues
    std::unique_lock lock(m_threadedProcessMutex);
    m_processes.clear();
    m_threadedProcesses.clear();
}

void ProcessQueue::reorderProcesses()
{
    // Reorder process vectors
    std::sort(m_processes.begin(), m_processes.end(), CompareBySortingLayer::s_compareBySortingLayer);
    std::sort(m_processQueue.begin(), m_processQueue.end(), CompareBySortingLayer::s_compareBySortingLayer);
}

void ProcessQueue::updateProcesses(unsigned long deltaMs)
{
    //// Update all processes on the main thread
    if (!m_processes.size()) {
        return;
    }

    std::vector<std::shared_ptr<Process>>::iterator it = m_processes.begin();
    while (it != m_processes.end())
    {
        // Grab the next process
        std::shared_ptr<Process> currentProcess = (*it);

        // Run process
        bool isDead = currentProcess->runProcess(deltaMs);

        // Only queue process to run again if it hasn't died
        if (!isDead) {
            m_processQueue.emplace_back(currentProcess);
        }
        // Process is destroyed if it is dead

        // Increment iterator 
        ++it;
    }

    // Swap process queue with iterable list
    m_processes.swap(m_processQueue);
    std::sort(m_processes.begin(), m_processes.end(), CompareBySortingLayer::s_compareBySortingLayer);
    m_processQueue.clear();


    //// Check that threaded processes haven't failed, and delete any that have completed
    {
        std::unique_lock lock(m_threadedProcessMutex);
        for (const std::shared_ptr<Process>& process : m_threadedProcesses) {
            std::shared_ptr<ThreadedProcess> threadedProcess = std::static_pointer_cast<ThreadedProcess>(process);
            threadedProcess->exceptionMutex().lock();
            const std::exception_ptr& ex = threadedProcess->exception();
            if (ex) {
                std::rethrow_exception(ex);
            }
            threadedProcess->exceptionMutex().unlock();

        }

        // In production code, here is where I would check to delete any
        // threaded processes that have completed
        //for (iterator over threaded processes) {
        //    if (threadedProcessFromIterator->isDead()) {
        //        deleteThreadedProcess(threadedProcess->id());
        //    }
        //    // Advance iterator
        //}
    }
}

void ProcessQueue::fixedUpdateProcesses(unsigned long deltaMs)
{
    std::vector<std::shared_ptr<Process>>::iterator it = m_processes.begin();
    while (it != m_processes.end())
    {
        // Grab the next process
        std::shared_ptr<Process> currentProcess = (*it);

        // Run process fixed update for process
        bool isDead = currentProcess->runFixed(deltaMs);

        // Only queue process to run again if it hasn't died
        if (!isDead) {
            m_processQueue.emplace_back(currentProcess);
        }
        // Process is destroyed if it is dead

        // Increment iterator 
        ++it;
    }

    // Swap process queue with iterable list
    m_processes.swap(m_processQueue);
    std::sort(m_processes.begin(), m_processes.end(), CompareBySortingLayer::s_compareBySortingLayer);
    m_processQueue.clear();

    return;
}

void ProcessQueue::attachProcess(const std::shared_ptr<Process>& process, bool initialize)
{
    if (!process->as<ThreadedProcess>()) {
        // Attach a non-threaded process
        m_processQueue.emplace_back(process);
        if (initialize) {
            process->onInit();
        }
    }
    else {
        // Add the threaded process to the asynchronous process queue
        m_threadedProcessMutex.lock();

        // Add threaded process to thread pool queue
        auto threadedProcess = std::dynamic_pointer_cast<ThreadedProcess>(process);
#ifdef DEBUG_MODE
        if (!threadedProcess) {
            throw("Wrong process type passed");
        }
#endif
        m_threadedProcesses.emplace_back(threadedProcess);
        m_threadedProcessMutex.unlock();

        // Start the threaded process, or at least queue it if no threads are available
        m_threadPool.addTask(std::bind(&ThreadedProcess::run, threadedProcess));
    }
}


void ProcessQueue::abortAllProcesses(bool immediate)
{
    // Clear standard processes
    if (m_processes.size()) {
        auto processes = m_processes;
        std::vector<std::shared_ptr<Process>>::iterator it = processes.begin();
        while (it != processes.end())
        {
            abortProcess(*it, immediate);
            ++it;
        }
    }

    // Clear threaded processes
    {
        std::unique_lock lock(m_threadedProcessMutex);

        if (m_threadedProcesses.size()) {

            std::vector<std::shared_ptr<Process>> threadedProcesses = m_threadedProcesses;
            std::vector<std::shared_ptr<Process>>::iterator thrit = threadedProcesses.begin();
            while (thrit != threadedProcesses.end())
            {
                abortProcess(*thrit, immediate);
                ++thrit;
            }
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // end namespacing
