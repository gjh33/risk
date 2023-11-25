#include "Log.h"

namespace debug {
	Log::Log() :
		m_Output(std::cout),
		m_Level(LogLevel::Debug)
	{
	}

	Log::Log(std::ostream& output) :
		m_Output(output),
		m_Level(LogLevel::Debug)
	{
	}

	void Log::SetLevelPermissable(LogLevel level) {
		m_Level = level;
	}

	void Log::Send(std::string message, LogLevel level) const {
		if (m_Level > level) return;
		switch (level) {
		case LogLevel::Debug:
			m_Output << "[DEBUG] " << message << std::endl;
			break;
		case LogLevel::Warning:
			m_Output << "[WARNING] " << message << std::endl;
			break;
		case LogLevel::Error:
			m_Output << "[ERROR] " << message << std::endl;
			break;
		}
	}

	void Log::Debug(std::string message) const {
		Send(message, LogLevel::Debug);
	}

	void Log::Warning(std::string message) const {
		Send(message, LogLevel::Warning);
	}

	void Log::Error(std::string message) const {
		Send(message, LogLevel::Error);
	}
}

