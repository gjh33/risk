#include "RiskResources.h"

#include <memory>

#include "resources/filters/FileExtensionResourceFilter.h"

namespace risk {
	const std::string RiskResources::MapFileExtension = "map";
	
	resources::Collection RiskResources::s_Collection("./");
	resources::FilteredCollectionView RiskResources::s_All(s_Collection);
	resources::FilteredCollectionView RiskResources::s_Maps = resources::FilteredCollectionView(s_Collection).Filter(std::make_shared<resources::FileExtensionResourceFilter>(MapFileExtension));

	void RiskResources::Init(std::string rootDirectory)
	{
		s_Collection = resources::Collection(rootDirectory);
		s_All = resources::FilteredCollectionView(s_Collection);
		s_Maps = resources::FilteredCollectionView(s_Collection).Filter(std::make_shared<resources::FileExtensionResourceFilter>(MapFileExtension));
	}

	const resources::FilteredCollectionView& RiskResources::All()
	{
		return s_All;
	}

	const resources::FilteredCollectionView& RiskResources::Maps()
	{
		return s_Maps;
	}

}
