///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "JLogger.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <core/memory/JMemoryCommon.h>
#include <core/diagnostics/JLogger.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace joby {

Logger & Logger::Get()
{
    return *s_instance;
}

void Logger::LogDebug(const char * msg)
{
#ifdef DEBUG_MODE
    Get().logMessage(msg, LogLevel::kDebug);
#else
    // Avoid unused message
    msg;
#endif
}

void Logger::LogInfo(const char * msg)
{
    Get().logMessage(msg, LogLevel::kInfo);
}

void Logger::LogWarning(const char * msg)
{
    Get().logMessage(msg, LogLevel::kWarning);
}

void Logger::LogError(const char * msg)
{
    Get().logMessage(msg, LogLevel::kError);
}

void Logger::LogCritical(const char * msg)
{
    Get().logMessage(msg, LogLevel::kCritical);
}

void Logger::logMessage(const char * message, LogLevel level)
{
    // Want to be able to be thread-safe
    std::unique_lock lock(m_loggerMutex);
    std::cout << s_levelNames[(size_t)level] << ":: " << message << std::endl;
}

Logger::Logger()
{
}
Logger::~Logger()
{
}

std::unique_ptr<Logger> Logger::s_instance = prot_make_unique<Logger>();

std::array<std::string, (size_t)LogLevel::COUNT> Logger::s_levelNames{ "Debug", "Info", "Warning", "Error", "Critical" };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // end namespaces