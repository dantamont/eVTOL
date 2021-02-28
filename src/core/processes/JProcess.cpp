#include "JProcess.h"
#include <core/diagnostics/JLogger.h>

namespace joby {
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool Process::runProcess(double sec)
{
    // Process is uninitialized, so checkValidity it
    if (getState() == ProcessState::kUninitialized) onInit();

    // Give the process an update tick if it's running
    if (getState() == ProcessState::kRunning) {
        onUpdate(sec);
    }

    // check to see if the process is dead
    bool dead = checkFinished();

    return dead;
}

bool Process::runFixed(double sec)
{
    // Process is uninitialized, so checkValidity it
    if (getState() == ProcessState::kUninitialized) onInit();

    // Give the process  fixedupdate tick if it's running
    if (getState() == ProcessState::kRunning) {
        onFixedUpdate(sec);
    }

    // check to see if the process is dead
    bool dead = checkFinished();

    //#ifdef DEBUG_MODE
    //    logMessage("Process:: Ran process fixed update");
    //#endif

    return dead;
}

bool Process::checkFinished()
{
    bool dead = isDead();
    if (dead)
    {
        // run the appropriate exit function
        switch (getState())
        {
        case ProcessState::kSucceeded:
        {
            onSuccess();
#ifdef DEBUG_MODE
            Logger::LogInfo("Successful process chain completion");
#endif
            break;
        }

        case ProcessState::kFailed:
        {
            onFail();
#ifdef DEBUG_MODE
            Logger::LogError("Failed process");
#endif
            break;
        }

        case ProcessState::kAborted:
        {
            onAbort();
#ifdef DEBUG_MODE
            Logger::LogWarning("Aborted process");
#endif
            break;
        }
        }
    }

    return dead;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // end namespacing
