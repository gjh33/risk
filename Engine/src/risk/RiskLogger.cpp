#include "RiskLogger.h"

namespace risk {
	static std::shared_ptr<const debug::Log> s_DefaultLog = std::make_shared<const debug::Log>();

	std::shared_ptr<const debug::Log> RiskLogger::s_Log;

	std::shared_ptr<const debug::Log> RiskLogger::GetLog() {
		if (s_Log == nullptr) return s_DefaultLog;
		return s_Log;
	}

	void RiskLogger::SetLog(std::shared_ptr<const debug::Log> log)
	{
		s_Log = log;
	}
}

