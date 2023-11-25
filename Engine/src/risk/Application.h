#pragma once

#include <string>

#include "debug/Log.h"

namespace risk
{
	class Application
	{
	public:
		Application();
		void Run();
		static const std::string& GetApplicationDirectory();
		static const std::string& GetResourcesDirectory();
	private:
		static const std::string ResourcesDirectoryName;
		
		static std::string s_ApplicationDirectory;
		static std::string s_ResourcesDirectory;
	};
}

