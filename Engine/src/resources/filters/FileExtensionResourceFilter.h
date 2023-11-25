#pragma once

#include <string>

#include "resources/IResourceFilter.h"
#include "resources/Resource.h"


namespace resources {
	class FileExtensionResourceFilter : public IResourceFilter
	{
	public:
		FileExtensionResourceFilter(std::string extension);
		bool operator()(const Resource& resource) override;
	private:
		std::string m_Extension;
	};
}

