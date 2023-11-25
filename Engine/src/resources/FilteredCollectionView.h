#pragma once

#include <memory>
#include <vector>
#include <string>

#include "Collection.h"
#include "IResourceFilter.h"
#include "Resource.h"

namespace resources {
	class FilteredCollectionIterator : public CollectionIterator
	{
	public:
		FilteredCollectionIterator() = default;
		FilteredCollectionIterator(std::string rootDirectory, std::vector<std::shared_ptr<IResourceFilter>> filters);
	protected:
		void IterateToNextValidResource() override;
	private:
		std::vector<std::shared_ptr<IResourceFilter>> m_Filters;

		bool Passes(Resource& resource);
	};

	class FilteredCollectionView
	{
	public:
		FilteredCollectionView(Collection collection);
		FilteredCollectionView& Filter(std::shared_ptr<IResourceFilter> filter);
		FilteredCollectionIterator begin() const;
		FilteredCollectionIterator end() const;

	private:
		Collection m_Collection;
		std::vector<std::shared_ptr<IResourceFilter>> m_Filters;
	};
}

