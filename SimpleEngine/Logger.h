#pragma once
#include <string>


enum class Level
{
    LOG_ALL = 0,
    // Display all logs
    LOG_TRACE,
    // Trace logging, intended for internal use only
    LOG_DEBUG,
    // Debug logging, used for internal debugging, it should be disabled on release builds
    LOG_INFO,
    // Info logging, used for program execution info
    LOG_WARNING,
    // Warning logging, used on recoverable failures
    LOG_ERROR,
    // Error logging, used on unrecoverable failures
    LOG_FATAL,
    // Fatal logging, used to abort program: exit(EXIT_FAILURE)
    LOG_NONE // Disable logging
};

enum class TimePrecision
{
    Seconds,
    Milliseconds,
    Microseconds,
    Nanoseconds
};

class Logger
{
public:
    static void Log(Level level, const std::string&& message);
    static void Log(Level level, const char* message);

    static void LogWithStackTrace(Level level, const std::string&& message);
    static void LogWithStackTrace(Level level, const char* message);

    static void LogPerformanceStart();
    static void LogPerformanceEnd(const char* message, TimePrecision precision = TimePrecision::Milliseconds,
                                  Level logLevel = Level::LOG_INFO);

    static void LogPerformanceAccumulateFrameStart(const std::string& key);
    static void LogPerformanceAccumulateFrameEnd(const std::string& key);
    static void LogPerformanceAccumulatedEnd(const std::string& key,
                                             TimePrecision precision = TimePrecision::Milliseconds,
                                             Level logLevel = Level::LOG_INFO);
};
