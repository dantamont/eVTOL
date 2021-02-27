#include "JTimer.h"
#include <sstream>

namespace joby {

Timer Timer::FromElapsedSeconds(double seconds)
{
    Timer timer;
    auto duration = std::chrono::duration_cast<std::chrono::steady_clock::duration>(
        std::chrono::duration<double, std::ratio<1, 1>>(seconds));
    timer.m_startTime = clock::now();
    timer.m_startTime = timer.m_startTime - duration;
    return timer;
}

std::time_t Timer::SteadyToTime_t(const clock::time_point & time)
{
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() +
        std::chrono::duration_cast<std::chrono::system_clock::duration>(time -
            std::chrono::steady_clock::now()));
}

Timer::Timer()
{
}

Timer::Timer(const Timer & other) :
    m_startTime(other.m_startTime),
    m_elapsedTime(other.m_elapsedTime)
{
}

Timer::~Timer()
{
}

Timer & Timer::operator=(const Timer & other)
{
    m_startTime = other.m_startTime;
    m_elapsedTime = other.m_elapsedTime;
    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// End namespaces        
}