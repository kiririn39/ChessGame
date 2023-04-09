#include "Logger.h"

#include <chrono>
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

inline static std::chrono::time_point<std::chrono::steady_clock> performanceTimeStart;

void Logger::LogPerformanceStart()
{
    performanceTimeStart = std::chrono::high_resolution_clock::now();
}

void Logger::LogPerformanceEnd(Level level, const char* message)
{
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - performanceTimeStart);

    std::string str;
    str.append(message);
    str.append(std::format(" miliseconds: {}", duration));

    Log(level, std::move(str));
}


