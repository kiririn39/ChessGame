#include "Logger.h"

#include <cassert>
#include <chrono>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "raylib.h"
#include "Utilities/Backward.h"
#include "Utilities/Format.h"


void Logger::Log(Level level, const std::string&& message)
{
	Log(level, message.c_str());
}

void Logger::Log(Level level, const char* message)
{
	TraceLog(static_cast<int>(level), message);
}

void Logger::LogWithStackTrace(Level level, const std::string& message)
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

inline static std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>> performanceTimeStarts;

void Logger::LogPerformanceStart()
{
	performanceTimeStarts.push_back(std::chrono::high_resolution_clock::now());
}

void Logger::LogPerformanceEnd(const char* message, TimePrecision precision, Level logLevel)
{
	auto end = std::chrono::high_resolution_clock::now();

	std::string str;
	str.append(message);

	if (precision == TimePrecision::Seconds)
		str.append(Engine::Format(" : %f",
				std::chrono::duration_cast<std::chrono::seconds>(end - performanceTimeStarts.back())));
	else if (precision == TimePrecision::Milliseconds)
		str.append(Engine::Format(" : %f",
				std::chrono::duration_cast<std::chrono::milliseconds>(end - performanceTimeStarts.back())));
	else if (precision == TimePrecision::Microseconds)
		str.append(Engine::Format(" : %f",
				std::chrono::duration_cast<std::chrono::microseconds>(end - performanceTimeStarts.back())));
	else
		assert(false);

	performanceTimeStarts.pop_back();

	Log(logLevel, std::move(str));
}

inline static std::unordered_map<std::string, std::chrono::time_point<std::chrono::high_resolution_clock>>
		accumulatedPerformanceStarts;
inline static std::unordered_map<std::string, std::chrono::duration<double>> accumulatedPerformance;

void Logger::LogPerformanceAccumulateFrameStart(const std::string& key)
{
	accumulatedPerformanceStarts[key] = std::chrono::high_resolution_clock::now();
}

void Logger::LogPerformanceAccumulateFrameEnd(const std::string& key)
{
	auto end = std::chrono::high_resolution_clock::now();
	accumulatedPerformance[key] += end - accumulatedPerformanceStarts[key];
}

void Logger::LogPerformanceAccumulatedEnd(const std::string& key, TimePrecision precision, Level logLevel)
{
	std::string str;
	str.append(key);

	if (precision == TimePrecision::Seconds)
		str.append(
				Engine::Format(" : %f", std::chrono::duration_cast<std::chrono::seconds>(accumulatedPerformance[key])));
	else if (precision == TimePrecision::Milliseconds)
		str.append(Engine::Format(
				" : %f", std::chrono::duration_cast<std::chrono::milliseconds>(accumulatedPerformance[key])));
	else if (precision == TimePrecision::Microseconds)
		str.append(Engine::Format(
				" : %f", std::chrono::duration_cast<std::chrono::microseconds>(accumulatedPerformance[key])));
	else
		assert(false);

	Log(logLevel, std::move(str));

	accumulatedPerformance.erase(key);
}
