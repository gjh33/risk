#pragma once

#include "Resource.h"

namespace resources {
	class IResourceFilter
	{
	public:
		virtual bool operator()(const Resource& resource) = 0;
	};
}
