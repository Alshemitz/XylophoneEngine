#include "DX3D/Core/Logger.h"
#include <iostream>
dx3d::Logger::Logger(LogLevel logLevel) : m_logLevel(logLevel)
{
	std::clog << "Xylophone Engine" << "\n";
	std::clog << "----------------" << "\n";
}

dx3d::Logger::~Logger()
{
}

void dx3d::Logger::log(LogLevel level, const char* message)
{
	auto logLevelToString = [](LogLevel level) -> const char*
	{
		switch (level)
		{
		case LogLevel::Error:
			return "ERROR";
		case LogLevel::Warning:
			return "WARNING";
		case LogLevel::Info:
			return "INFO";
		default:
			return "UNKNOWN";
		}
		};

	if (level > m_logLevel) 
		return;
	std::clog << "[DX3D " << logLevelToString(level) << "]: " << message << "\n";
}
