#pragma once

#include <memory>

#include "debug/Log.h"

namespace risk {
	class RiskLogger
	{
	public:
		static std::shared_ptr<const debug::Log> GetLog();
		static void SetLog(std::shared_ptr<const debug::Log> log);

	private:
		static std::shared_ptr<const debug::Log> s_Log;
	};
}

