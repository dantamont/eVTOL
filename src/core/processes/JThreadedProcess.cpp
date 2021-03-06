#include "JThreadedProcess.h"
#include <core/time/JTimer.h>

namespace joby {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
ThreadedProcess::ThreadedProcess():
    Process(),
    m_previousElapsedTime(0)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
ThreadedProcess::~ThreadedProcess()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ThreadedProcess::onSuccess()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ThreadedProcess::run()
{
    // Initialize a timer for the threaded process
    Timer timer;
    timer.start();
    double newTime = 0;
    m_previousElapsedTime = 0;

    // Run the threaded process until it's dead
    while (isAlive()) {
        newTime = timer.getElapsed<double>();
        if (!isPaused()) {
            double dt = newTime - m_previousElapsedTime;
            runProcess(dt);
        }
        m_previousElapsedTime = newTime;
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // End namespaces