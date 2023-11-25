#include "Continent.h"

namespace risk {
	Continent::Continent(std::string name, int bonus) :
		m_Name(name),
		m_Bonus(bonus)
	{
	}

	std::string Continent::GetName() const
	{
		return m_Name;
	}
	
	int Continent::GetBonus() const
	{
		return m_Bonus;
	}
}
