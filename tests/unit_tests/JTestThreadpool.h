#ifndef TEST_THREADPOOL_H
#define TEST_THREADPOOL_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../JTest.h"
#include <core/threading/JThreadPool.h>
#include <core/containers/JString.h>
#include <core/diagnostics/JLogger.h>

namespace joby{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tests
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ThreadpoolTest : public Test
{
public:

    ThreadpoolTest(): Test(){}
    ~ThreadpoolTest() {}

    /// @brief Perform unit tests for Timer class
    virtual void perform() {

        ThreadPool pool;
        Logger::LogInfo(JString::Format("Running thread pool with %d threads", pool.numThreads()).c_str());

        for (size_t i = 0; i < 100; i++) {
            pool.addTask([i, &pool]() {
                auto thread_id = std::this_thread::get_id();
                size_t id = pool.getIndex(thread_id);
                Logger::LogInfo(JString::Format("I am job %d on thread %d", (size_t)i, id).c_str());
            });
        }

    }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End namespaces
}


#endif