#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Continent.h"
#include "Territory.h"

namespace risk {
	class Map
	{
	public:
		Map(std::string name, std::string author, std::vector<std::shared_ptr<Continent>> continents, std::vector<std::shared_ptr<Territory>> territories);
		bool IsValid() const;
	private:
		const std::string m_Name;
		const std::string m_Author;
		const std::vector<std::shared_ptr<Continent>> m_Continents;
		const std::vector<std::shared_ptr<Territory>> m_Territories;

		bool m_IsValid;

		void Validate();
	};
}

