#pragma once

#include <string>
#include <memory>

#include "Map.h"

namespace risk {
	class MapLoader
	{
	public:
		static std::shared_ptr<Map> FromFile(std::string filePath);
	};
}

