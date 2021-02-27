#ifndef J_LOGGER_H
#define J_LOGGER_H
/** @file JLogger.h 
    Defines a basic message logging system.
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Standard
#include <string>
#include <array>
#include <mutex>

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
/// @brief Defines some named log levels.
/// @details Log levels range from 0 to 100, with 100 representing a critical error and lower numbers describe
/// lesser errors, informational messages and debugging messages.
enum class LogLevel : unsigned int {
    kDebug,
    kInfo,
    kWarning,
    kError,
    kCritical,
    COUNT
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @class Logger
/// @brief A singleton Logger class to be used for standardized message logging
class Logger {
public:
    //-----------------------------------------------------------------------------------------------------------------
    /// @name Static Methods
    /// @{

    /// @brief Get the singleton instance of Logger
    static Logger& Get();

    // NOTE, in operational code, I would template these to allow for other string
    // types, such as std::string
    /// @brief Convenience methods for logging
    static void LogDebug(const char* msg);
    static void LogInfo(const char* msg);
    static void LogWarning(const char* msg);
    static void LogError(const char* msg);
    static void LogCritical(const char* msg);

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Destructor
    /// @{

    ~Logger();

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Properties
    /// @{
    /// @}

    //-----------------------------------------------------------------------------------------------------------------
	/// @name Public Methods
	/// @{
    /// @brief Output a log message
    /// @param[in] message Message is the descriptive message of log.
    /// @param[in] level The level for the message.  The higher the value, the more severe the issue.
    void logMessage(const char* message, LogLevel level);

	/// @}
protected:

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Constructor
    /// @{

    Logger();

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Members
    /// @{

    std::mutex m_loggerMutex;

    /// @}

    //-----------------------------------------------------------------------------------------------------------------
    /// @name Static
    /// @{

    /// @brief The singleton instance of the loger
    static std::unique_ptr<Logger> s_instance;

    /// @brief The header strings to be prepended to messages of each LogLevel
    static std::array<std::string, (size_t)LogLevel::COUNT> s_levelNames;

    /// @}


};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // end namespacing

#endif