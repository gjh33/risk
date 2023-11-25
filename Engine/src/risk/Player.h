#pragma once

#include <string>

namespace risk {
	class Player
	{
	public:
		Player(std::string name);
		std::string GetName() const;
	private:
		const std::string m_Name;
	};
}

