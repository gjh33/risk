#include "MapFile.h"

#include <filesystem>
#include <fstream>
#include <sstream>

#include "Logging.h"

namespace risk {
	const std::string MapFile::MapFileHeader = "[map]";
	const std::string MapFile::ContintentsFileHeader = "[continents]";
	const std::string MapFile::TerritoriesFileHeader = "[territories]";
	const std::string MapFile::ImageVariableName = "image";
	const std::string MapFile::WrapVariableName = "wrap";
	const std::string MapFile::ScrollVariableName = "scroll";
	const std::string MapFile::AuthorVariableName = "author";
	const std::string MapFile::WarnVariableName = "warn";
	const std::string MapFile::VariableYesValue = "yes";
	const std::string MapFile::VariableHorizontalScrollValue = "horizontal";
	const std::string MapFile::VariableVerticalScrollValue = "vertical";
	const std::string MapFile::VariableNoneScrollValue = "none";
	const char MapFile::VariableDelimeter = '=';
	const char MapFile::TerritoryDelimeter = ',';
	const int MapFile::TerritoryMinTokenCount = 4;
	
	MapFile::MapFile(std::string path) :
		m_Path(path),
		m_Name(std::filesystem::path(path).stem().string()),
		m_Data()
	{
		m_ParsedSuccessfully = TryParse();
	}

	bool MapFile::IsValid() const
	{
		return m_ParsedSuccessfully;
	}

	MapFile::FileData MapFile::GetData() const
	{
		return m_Data;
	}

	std::string MapFile::GetName() const
	{
		return m_Name;
	}

	// We support some extra cases:
	// Files don't need to define headers in a particular order
	// Map header does not need to define variables in a particular order
	// Parsing is case invariant for headers and variable identifiers
	// File may omit map header variables and they will default
	// For yes/no values, anything other than yes is counted as false
	// Can have empty lines anywhere
	// Not all sections must be defined, but they will have default values
	bool MapFile::TryParse()
	{
		if (!std::filesystem::exists(m_Path)) {
			ERROR("Map file does not exist: " + m_Path);
			return false;
		}

		// used for validation of successful parse
		bool hasParsedMap = false;
		bool hasParsedContinents = false;
		bool hasParsedTerritories = false;

		std::ifstream file(m_Path);
		std::string line;

		// first line
		std::getline(file, line);

		while (file.peek() != EOF) {
			// Read until we reach a header
			while (file.peek() != EOF && !IsHeader(line)) std::getline(file, line);

			// get lowercase header
			std::string header = line;
			std::transform(header.begin(), header.end(), header.begin(), ::tolower);
			
			// If it's a map header, we load map data
			if (header == MapFileHeader) {
				// Don't parse more than once
				if (hasParsedMap) {
					ERROR("Map file has multiple " + MapFileHeader + " headers: " + m_Path);
					return false;
				}
				// mark we've parsed the map
				hasParsedMap = true;

				// next line
				std::getline(file, line);

				// parse map variables until we reach EOF or another header
				while (file.peek() != EOF && !IsHeader(line)) {
					// check for delimeter
					std::string::iterator delimeter = std::find(line.begin(), line.end(), VariableDelimeter);

					// If no delimeter found, invalid line and we ignore it
					// might be whitespace
					if (delimeter == line.end()) {
						std::getline(file, line);
						continue;
					}

					// split line into before and after token (=)
					std::string before = line.substr(0, delimeter - line.begin());
					std::string after = line.substr(delimeter - line.begin() + 1);

					// lowercase the variable name
					std::transform(before.begin(), before.end(), before.begin(), ::tolower);

					if (before == ImageVariableName) {
						m_Data.Map.Image = after;
					}
					else if (before == WrapVariableName) {
						m_Data.Map.Wrap = after == VariableYesValue;
					}
					else if (before == ScrollVariableName) {
						if (after == VariableVerticalScrollValue) m_Data.Map.Scroll = MapFile::MapScrollMode::Vertical;
						else if (after == VariableHorizontalScrollValue) m_Data.Map.Scroll = MapFile::MapScrollMode::Horizontal;
						else if (after == VariableNoneScrollValue) m_Data.Map.Scroll = MapFile::MapScrollMode::None;
						else {
							ERROR("Map file has invalid scroll value: " + after + " in " + m_Path);
							return false;
						}
					}
					else if (before == AuthorVariableName) {
						m_Data.Map.Author = after;
					}
					else if (before == WarnVariableName) {
						m_Data.Map.Warn = after == VariableYesValue;
					}
					else {
						ERROR("Map file has invalid variable: " + before + " in " + m_Path);
						return false;
					}

					// next line and go again
					std::getline(file, line);
				}
			}
			else if (header == ContintentsFileHeader) {
				if (hasParsedContinents) {
					ERROR("Map file has multiple " + ContintentsFileHeader + " headers: " + m_Path);
					return false;
				}
				hasParsedContinents = true;
				
				// next line
				std::getline(file, line);

				// parse map variables until we reach EOF or another header
				while (file.peek() != EOF && !IsHeader(line)) {
					// check for delimeter
					std::string::iterator delimeter = std::find(line.begin(), line.end(), VariableDelimeter);

					// If no delimeter found, invalid line and we ignore it
					// might be whitespace
					if (delimeter == line.end()) {
						std::getline(file, line);
						continue;
					}

					// split line into before and after token (=)
					std::string before = line.substr(0, delimeter - line.begin());
					std::string after = line.substr(delimeter - line.begin() + 1);

					int bonus = std::stoi(after);

					ContinentData continent = { before, bonus };

					m_Data.Continents.push_back(continent);

					// next line and go again
					std::getline(file, line);
				}
			}
			else if (header == TerritoriesFileHeader) {
				if (hasParsedTerritories) {
					ERROR("Map file has multiple " + TerritoriesFileHeader + " headers: " + m_Path);
					return false;
				}
				hasParsedTerritories = true;

				// next line
				std::getline(file, line);

				// parse map variables until we reach EOF or another header
				while (file.peek() != EOF && !IsHeader(line)) {
					// check for delimeter
					std::string::iterator delimeter = std::find(line.begin(), line.end(), TerritoryDelimeter);

					// If no delimeter found, invalid line and we ignore it
					// might be whitespace
					if (delimeter == line.end()) {
						std::getline(file, line);
						continue;
					}

					std::stringstream linestream(line);
					std::vector<std::string> tokens;
					tokens.reserve(4);
					
					while (linestream.good()) {
						std::string token;
						std::getline(linestream, token, TerritoryDelimeter);
						tokens.push_back(token);
					}

					if (tokens.size() < TerritoryMinTokenCount) {
						ERROR("Map file has invalid territory line: " + line + " in " + m_Path);
						return false;
					}

					// Fill mandatory data
					TerritoryData territory = { tokens[0], std::stoi(tokens[1]), std::stoi(tokens[2]), tokens[3] };

					// Add remaining data
					for (int i = TerritoryMinTokenCount; i < tokens.size(); i++) {
						territory.Neighbours.push_back(tokens[i]);
					}

					m_Data.Territories.push_back(territory);

					// next line and go again
					std::getline(file, line);
				}
			}
		}

		return true;
	}

	bool MapFile::IsHeader(std::string text) const
	{
		std::transform(text.begin(), text.end(), text.begin(), ::tolower);
		if (text == MapFileHeader) return true;
		if (text == ContintentsFileHeader) return true;
		if (text == TerritoriesFileHeader) return true;
		return false;
	}
}
