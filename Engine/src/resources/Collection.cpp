#include "Collection.h"

namespace resources {
	CollectionIterator::CollectionIterator(std::string rootDirectory) :
		m_RootDirectory(rootDirectory),
		m_Iterator(std::filesystem::recursive_directory_iterator(rootDirectory)),
		m_End(std::filesystem::recursive_directory_iterator())
	{
		IterateToNextValidResource();
	}

	Resource& CollectionIterator::operator*()
	{
		return m_Current;
	}

	const Resource& CollectionIterator::operator*() const
	{
		return m_Current;
	}

	Resource* CollectionIterator::operator->()
	{
		return &m_Current;
	}


	const Resource* CollectionIterator::operator->() const
	{
		return &m_Current;
	}

	CollectionIterator& CollectionIterator::operator++()
	{
		m_Iterator++;
		IterateToNextValidResource();
		return *this;
	}

	CollectionIterator CollectionIterator::operator++(int)
	{
		CollectionIterator oldValue = *this;
		++(*this);
		return oldValue;
	}

	bool operator==(const CollectionIterator& a, const CollectionIterator& b)
	{
		return a.m_Current == b.m_Current;
	}

	bool operator!=(const CollectionIterator& a, const CollectionIterator& b)
	{
		return a.m_Current != b.m_Current;
	}

	void CollectionIterator::UpdateCurrent()
	{
		if (m_Iterator == m_End) {
			m_Current = Resource();
		}
		else {
			m_Current = Resource(m_Iterator->path().string());
		}
	}

	void CollectionIterator::IterateToNextValidResource()
	{
		while (m_Iterator != m_End && !m_Iterator->is_regular_file()) m_Iterator++;
		UpdateCurrent();
	}

	Collection::Collection(std::string rootDirectory) :
		m_RootDirectory(rootDirectory)
	{
	}

	std::string Collection::GetRootDirectory() const
	{
		return m_RootDirectory;
	}

	CollectionIterator Collection::begin() 
	{
		return CollectionIterator(m_RootDirectory);
	}

	CollectionIterator Collection::end()
	{
		return CollectionIterator();
	}
}
