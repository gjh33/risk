#pragma once

#include <string>

namespace risk {
	class Continent
	{
	public:
		Continent(std::string name, int bonus);
		std::string GetName() const;
		int GetBonus() const;
	private:
		const std::string m_Name;
		const int m_Bonus;
	};
}

