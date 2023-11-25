#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Player.h"
#include "Continent.h"
	
namespace risk {
	class Territory
	{
	public:
		Territory(std::string name, std::shared_ptr<Continent> continent);
		std::string GetName() const;
		void SetOwner(std::shared_ptr<Player> player);
		std::shared_ptr<Player> GetOwner() const;
		std::vector<std::shared_ptr<Territory>> GetAdjacentTerritories() const;
		void AddNeighbour(std::shared_ptr<Territory> territory);
		void RemoveNeighbour(std::shared_ptr<Territory> territory);
		bool HasNeighbour(std::shared_ptr<Territory> territory) const;
		std::shared_ptr<Continent> GetContinent() const;

	private:
		const std::string m_Name;
		const std::shared_ptr<Continent> m_Continent;
		std::vector<std::shared_ptr<Territory>> m_AdjacentTerritories;
		std::shared_ptr<Player> m_Owner;
	};
}

