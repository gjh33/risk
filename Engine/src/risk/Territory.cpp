#include "Territory.h"

namespace risk {
	Territory::Territory(std::string name, std::shared_ptr<Continent> continent) :
		m_Name(name),
		m_Continent(continent)
	{
	}

	std::string Territory::GetName() const
	{
		return m_Name;
	}

	void Territory::SetOwner(std::shared_ptr<Player> player)
	{
		m_Owner = player;
	}

	std::shared_ptr<Player> Territory::GetOwner() const
	{
		return m_Owner;
	}

	std::vector<std::shared_ptr<Territory>> Territory::GetAdjacentTerritories() const
	{
		return m_AdjacentTerritories;
	}

	void Territory::AddNeighbour(std::shared_ptr<Territory> territory)
	{
		m_AdjacentTerritories.push_back(territory);
	}

	void Territory::RemoveNeighbour(std::shared_ptr<Territory> territory)
	{
		std::vector<std::shared_ptr<Territory>>::iterator element = std::find(m_AdjacentTerritories.begin(), m_AdjacentTerritories.end(), territory);
		if (element != m_AdjacentTerritories.end())
		{
			m_AdjacentTerritories.erase(element);
		}
	}

	bool Territory::HasNeighbour(std::shared_ptr<Territory> territory) const
	{
		return std::find(m_AdjacentTerritories.begin(), m_AdjacentTerritories.end(), territory) != m_AdjacentTerritories.end();
	}

	std::shared_ptr<Continent> Territory::GetContinent() const
	{
		return m_Continent;
	}
}
