#pragma once

#include <stdexcept> // required for std::runtime_error used by macros



namespace dx3d
{
	class Logger final
	{
	public:
		enum class LogLevel
		{
			Error = 0,
			Warning,
			Info,
		};

		explicit Logger(LogLevel logLevel = LogLevel::Error);
		~Logger();
		void log(LogLevel level, const char* message);

	protected:
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;

	private:
		LogLevel m_logLevel = LogLevel::Error;
	};
}

// Note: keep getLogger() declaration/definition elsewhere in the codebase.
#define DX3DLogInfo(message) \
	do { getLogger().log(dx3d::Logger::LogLevel::Info, (message)); } while(0)

#define DX3DLogWarning(message) \
	do { getLogger().log(dx3d::Logger::LogLevel::Warning, (message)); } while(0)

#define DX3DLogError(message) \
	do { getLogger().log(dx3d::Logger::LogLevel::Error, (message)); } while(0)

#define DX3DLogErrorAndThrow(message) \
	do { getLogger().log(dx3d::Logger::LogLevel::Error, (message)); throw std::runtime_error(message); } while(0)