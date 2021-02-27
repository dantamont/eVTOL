/////////////////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GB_TIMER_H
#define GB_TIMER_H

// std
#include <chrono>
#include <iomanip> // For std::time_t

namespace joby {


/////////////////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
// Class definitions
/////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Timer class for managing simulation time
/// @details This is essentially a wrapper around std::chrono
class Timer {
private:
    using clock = std::chrono::steady_clock;

    //--------------------------------------------------------------------------------------------
    /// @name Private Members
    /// @{

    clock::time_point m_startTime = {};
    clock::duration m_elapsedTime = {};

    /// @}
public:
    //--------------------------------------------------------------------------------------------
    /// @name Static
    /// @{

    /// @brief Convience methods to convert clock durations to specified units
    template<typename Rep>
    static Rep ToSeconds(const clock::duration& duration) {
        return std::chrono::duration<Rep>(duration).count();
    }

    /// @brief Create a timer that initialized the specified number of seconds ago
    static Timer FromElapsedSeconds(double seconds);

    /// @brief Convert steady clock time to time_t
    static std::time_t SteadyToTime_t(const clock::time_point& time);

    /// @}

    //--------------------------------------------------------------------------------------------
    /// @name Constructors/Destructor
    /// @{

    Timer();
    Timer(const Timer& other);
    ~Timer();

    /// @}

    //--------------------------------------------------------------------------------------------
    /// @name Properties
    /// @{

    const clock::time_point& startTime() const {
        return m_startTime;
    }

    /// @}

    //--------------------------------------------------------------------------------------------
    /// @name Operators
    /// @{

    Timer& operator=(const Timer& other);

    /// @}

    //--------------------------------------------------------------------------------------------
    /// @name Public methods
    /// @{

    /// @brief Whether or not the clock is currently counting time
    /// @details Timer is running if start time is not a null time point
    bool isRunning() const {
        return m_startTime != clock::time_point{};
    }

    /// @brief Restart the timer, returning the elapsed time as a duration
    clock::duration restart() {
        // Stop to cache elapsed time
        stop();
        clock::duration elapsedTime(m_elapsedTime);

        // Reset to clear elapsed time
        reset();

        // Start clock again
        start();

        return elapsedTime;
    }

    /// @brief Start the timer, doing nothing if already running
    void start() {
        // Only start of not running
        if (!isRunning()) {
            m_startTime = clock::now();
        }
    }

    /// @brief Stop the timer, caching the elapsed time
    void stop() {
        if (isRunning()) {
            m_elapsedTime += clock::now() - m_startTime;
            m_startTime = {};
        }
    }

    /// @brief Clear the timer
    void reset() {
        m_startTime = {};
        m_elapsedTime = {};
    }

    /// @brief Get elapsed time as a clock duration
    clock::duration getElapsedDuration() const {
        auto result = m_elapsedTime;
        if (isRunning()) {
            result += clock::now() - m_startTime;
        }
        return result;
    }

    /// @brief Return elapsed time in seconds, with given type
    /// @example std::chrono::duration<Rep, std::milli> would return milliseconds
    template<typename Rep>
    Rep getElapsed() const {
        return ToSeconds<Rep>(getElapsedDuration());
    }

    /// @}
};


/////////////////////////////////////////////////////////////////////////////////////////////
} // End namespaces

#endif