#include "FilteredCollectionView.h"

namespace resources {
	FilteredCollectionIterator::FilteredCollectionIterator(std::string rootDirectory, std::vector<std::shared_ptr<IResourceFilter>> filters) :
		CollectionIterator(rootDirectory),
		m_Filters(filters)
	{
		IterateToNextValidResource();
	}

	void FilteredCollectionIterator::IterateToNextValidResource()
	{
		while (m_Iterator != m_End && !m_Iterator->is_regular_file()) m_Iterator++;
		UpdateCurrent();
		if (m_Iterator == m_End) return;
		if (Passes(m_Current)) return;
		m_Iterator++;
		IterateToNextValidResource();
	}

	bool FilteredCollectionIterator::Passes(Resource& resource)
	{
		bool passes = true;
		for (auto filter : m_Filters)
		{
			passes &= (*filter)(resource);
			if (!passes) break;
		}
		return passes;
	}
	
	FilteredCollectionView::FilteredCollectionView(Collection collection) :
		m_Collection(collection)
	{
	}

	FilteredCollectionView& FilteredCollectionView::Filter(std::shared_ptr<IResourceFilter> filter)
	{
		m_Filters.push_back(filter);
		return *this;
	}

	FilteredCollectionIterator FilteredCollectionView::begin() const
	{
		return FilteredCollectionIterator(m_Collection.GetRootDirectory(), m_Filters);
	}

	FilteredCollectionIterator FilteredCollectionView::end() const
	{
		return FilteredCollectionIterator();
	}

}
