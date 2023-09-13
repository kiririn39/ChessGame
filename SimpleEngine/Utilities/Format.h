//
// Created by Vlad Boroday on 2023-04-15.
//

#pragma once

#include <string>
//#include <boost/format.hpp>

namespace Engine
{
	template<typename... Args>
	static inline std::string Format(const char* message, Args&& ... args)
	{
		return {};//(boost::format(message) % ... % std::forward<Args>(args)).str();
	}

	template<typename... Args>
	static inline std::string FormatString(const std::string& message, Args&& ... args)
	{
		return Format(message, std::forward<Args>(args)...);
	}
}