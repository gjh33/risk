#include "MapLoader.h"

#include<unordered_map>

#include "Logging.h"
#include "MapFile.h"

namespace risk {
	std::shared_ptr<Map> MapLoader::FromFile(std::string filePath)
	{
		MapFile mapFile(filePath);
		if (!mapFile.IsValid())
		{
			ERROR("Map file is invalid: " + filePath);
			return nullptr;
		}

		std::unordered_map<std::string, std::shared_ptr<Continent>> continents;
		std::unordered_map<std::string, std::shared_ptr<Territory>> territories;

		MapFile::FileData data = mapFile.GetData();

		// make our continents
		for (MapFile::ContinentData continentData : data.Continents)
		{
			std::shared_ptr<Continent> continent = std::make_shared<Continent>(continentData.Name, continentData.Bonus);
			continents[continentData.Name] = continent;
		}
		
		// make our territories
		for (MapFile::TerritoryData territoryData : data.Territories)
		{
			std::shared_ptr<Continent> continent = continents[territoryData.Continent];

			// verify continent exists
			if (continent == nullptr) {
				ERROR("Territory " + territoryData.Name + " has invalid continent " + territoryData.Continent);
				return nullptr;
			}

			std::shared_ptr<Territory> territory = std::make_shared<Territory>(territoryData.Name, continent);

			territories[territoryData.Name] = territory;
		}

		// second pass to wire up neighbours
		for (MapFile::TerritoryData territoryData : data.Territories)
		{
			// we can logically deduce it must exist as we just made it
			std::shared_ptr<Territory> territory = territories[territoryData.Name];

			for (std::string neighbour : territoryData.Neighbours)
			{
				std::shared_ptr<Territory> neighbourTerritory = territories[neighbour];
				// verify neighbour exists
				if (neighbourTerritory == nullptr) {
					ERROR("Territory " + territoryData.Name + " has invalid neighbour " + neighbour);
					return nullptr;
				}

				if (territory->HasNeighbour(neighbourTerritory))
				{
					WARN("Ignoring duplicate neighbour! Territory " + territoryData.Name + " already has neighbour " + neighbour);
				}
				else {
					territory->AddNeighbour(territories[neighbour]);
				}
			}
		}

		// convert maps to vectors
		std::vector<std::shared_ptr<Continent>> continentVector;
		std::vector<std::shared_ptr<Territory>> territoryVector;
		
		for (std::pair<const std::string, std::shared_ptr<Continent>>& continent : continents)
		{
			continentVector.push_back(continent.second);
		}
		
		for (std::pair<const std::string, std::shared_ptr<Territory>>& territory : territories)
		{
			territoryVector.push_back(territory.second);
		}
		
		// make our map
		std::shared_ptr<Map> map = std::make_shared<Map>(mapFile.GetName(), data.Map.Author, continentVector, territoryVector);

		// validate it
		if (!map->IsValid())
		{
			ERROR("Map is invalid: " + filePath);
			return nullptr;
		}

		return map;
	}
}
