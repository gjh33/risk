#include "Resource.h"

#include <filesystem>

namespace resources {
	Resource::Resource(std::string path) :
		m_Path(path),
		m_Name(std::filesystem::path(path).filename().string())
	{
	}

	std::string Resource::GetName() const
	{
		return m_Name;
	}

	std::string Resource::GetPath() const
	{
		return m_Path;
	}
}
