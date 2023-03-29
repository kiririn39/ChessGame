#include "Logger.h"

#include <iostream>
#include <sstream>
#include "External/raylib/src/raylib.h"
#include "Backward/backward.h"


void Logger::Log(Level level, const std::string&& message)
{
    Log(level, message.c_str());
}

void Logger::Log(Level level, const char* message)
{
    TraceLog(static_cast<int>(level), message);
}

void Logger::LogWithStackTrace(Level level, const std::string&& message)
{
    LogWithStackTrace(level, message.c_str());
}

void Logger::LogWithStackTrace(Level level, const char* message)
{
    TraceLog(static_cast<int>(level), message);

    if (level >= Level::LOG_DEBUG)
    {
        std::cout << Backward::GetStackTrace().str();
        fflush(stdout);
    }
}
