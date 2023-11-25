#include "Map.h"

#include <unordered_set>
#include <stack>

namespace risk {
    Map::Map(std::string name, std::string author, std::vector<std::shared_ptr<Continent>> continents, std::vector<std::shared_ptr<Territory>> territories) :
		m_Name(name),
		m_Author(author),
		m_Continents(continents),
		m_Territories(territories),
		m_IsValid(false)
    {
		Validate();
    }

	bool Map::IsValid() const
	{
		return m_IsValid;
	}

	void Map::Validate()
	{
		// verify territories are a single connected graph
		std::unordered_set<std::shared_ptr<Territory>> visited;
		std::stack<std::shared_ptr<Territory>> toVisit;

		toVisit.push(m_Territories[0]);

		std::shared_ptr<Territory> current;
		do
		{
			current = toVisit.top();
			toVisit.pop();

			visited.insert(current);
			for (std::shared_ptr<Territory> neighbour : current->GetAdjacentTerritories())
			{
				if (!visited.contains(neighbour)) {
					toVisit.push(neighbour);
				}
			}
		} while (!toVisit.empty());
		
		m_IsValid &= visited.size() == m_Territories.size();

		// verify continents are connected to at least one territory
		std::unordered_set<std::shared_ptr<Continent>> visitedContinents;

		for (std::shared_ptr<Territory> territory : m_Territories)
		{
			visitedContinents.insert(territory->GetContinent());
		}

		m_IsValid &= visitedContinents.size() == m_Continents.size();
	}
}
