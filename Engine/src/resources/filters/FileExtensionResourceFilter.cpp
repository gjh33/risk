#include "FileExtensionResourceFilter.h"

#include <filesystem>

namespace resources {
	FileExtensionResourceFilter::FileExtensionResourceFilter(std::string extension) :
		m_Extension(extension[0] == '.' ? extension : "." + extension)
	{
	}

	bool FileExtensionResourceFilter::operator()(const Resource& resource)
	{
		std::string extention = std::filesystem::path(resource.GetPath()).extension().string();
		return extention == m_Extension;
	}
}
