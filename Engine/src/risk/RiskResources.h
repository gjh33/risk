#pragma once

#include <string>

#include "resources/Collection.h"
#include "resources/FilteredCollectionView.h"

namespace risk {
	class RiskResources
	{
	public:
		static void Init(std::string rootDirectory);
		static const resources::FilteredCollectionView& All();
		static const resources::FilteredCollectionView& Maps();
	private:
		static const std::string MapFileExtension;
		static resources::Collection s_Collection;
		static resources::FilteredCollectionView s_All;
		static resources::FilteredCollectionView s_Maps;
	};
}

