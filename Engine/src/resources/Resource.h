#pragma once

#include <string>

namespace resources {
	class Resource
	{
	public:
		Resource() = default;
		Resource(std::string path);
		std::string GetName() const;
		std::string GetPath() const;
		friend bool operator==(const Resource& a, const Resource& b) = default;
		friend bool operator!=(const Resource& a, const Resource& b) = default;
	private:
		std::string m_Path;
		std::string m_Name;
	};
}

