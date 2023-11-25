#pragma once

#include <string>

#include "Map.h"

namespace risk {
	class MapFile
	{
	public:
		enum MapScrollMode 
		{
			None,
			Horizontal,
			Vertical,
		};

		struct MapData 
		{
			std::string Image;
			bool Wrap;
			MapScrollMode Scroll;
			std::string Author;
			bool Warn;
		};

		struct ContinentData
		{
			std::string Name;
			int Bonus;
		};

		struct TerritoryData
		{
			std::string Name;
			int XPos;
			int YPos;
			std::string Continent;
			std::vector<std::string> Neighbours;
		};

		struct FileData
		{
			MapData Map;
			std::vector<ContinentData> Continents;
			std::vector<TerritoryData> Territories;
		};
		
	public:
		MapFile(std::string path);
		bool IsValid() const;
		FileData GetData() const;
		std::string GetName() const;
	private:
		static const std::string MapFileHeader;
		static const std::string ContintentsFileHeader;
		static const std::string TerritoriesFileHeader;
		static const std::string ImageVariableName;
		static const std::string WrapVariableName;
		static const std::string ScrollVariableName;
		static const std::string AuthorVariableName;
		static const std::string WarnVariableName;
		static const std::string VariableYesValue;
		static const std::string VariableHorizontalScrollValue;
		static const std::string VariableVerticalScrollValue;
		static const std::string VariableNoneScrollValue;
		static const char VariableDelimeter;
		static const char TerritoryDelimeter;
		static const int TerritoryMinTokenCount;
		
		const std::string m_Path;
		const std::string m_Name;

		bool m_ParsedSuccessfully;
		FileData m_Data;
		
		bool TryParse();
		bool IsHeader(std::string line) const;
	};
}

