#include "JSimulator.h"
#include <core/time/JTimer.h>

namespace joby {
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Simulator::Simulator(size_t numHelperThreads):
    m_processQueue(numHelperThreads)
{
}

Simulator::~Simulator()
{
}

void Simulator::simulate(std::function<bool(double)> pred, const double timeStepSec)
{
    // Initialize timing-related locals
    double simulationTime = 0.0;
    double totalElapsedTime = 0.0;
    double previousTime = 0.0;
    double accumulator = 0.0;

    // Start the simulation timer
    Timer timer;
    timer.start();

    // Run while the predicate returns true
    while (!pred(totalElapsedTime))
    {
        // Input/event handling logic would go here in production code

        double timeSinceLastFrame = totalElapsedTime - previousTime;
        accumulator += timeSinceLastFrame;

        // Perform fixed-step simulation until up-to-date
        while (accumulator >= timeStepSec)
        {
            // Update all simulation processes
            m_processQueue.updateProcesses(timeStepSec);

            // Increment simulation time one step forward
            accumulator -= timeStepSec;
            simulationTime += timeStepSec;
        }

        // Rendering logic would go here in production code

        // Update total elapsed time
        previousTime = totalElapsedTime;
        totalElapsedTime = timer.getElapsed<double>();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // end namespacing
