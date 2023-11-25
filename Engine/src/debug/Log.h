#pragma once

#include <string>
#include <iostream>

namespace debug {
	enum LogLevel {
		Debug,
		Warning,
		Error
	};
	
	class Log
	{
	public:
		Log();
		Log(std::ostream& output);
		void SetLevelPermissable(LogLevel level);
		void Send(std::string message, LogLevel level) const;
		void Debug(std::string message) const;
		void Warning(std::string message) const;
		void Error(std::string message) const;

	private:
		std::ostream& m_Output;
		LogLevel m_Level;
	};
}

