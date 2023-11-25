#pragma once

#include <string>
#include <filesystem>

#include "Resource.h"

namespace resources {
	class CollectionIterator {
	public:
		CollectionIterator() = default;
		CollectionIterator(std::string rootDirectory);
		Resource& operator*();
		const Resource& operator*() const;
		Resource* operator->();
		const Resource* operator->() const;
		CollectionIterator& operator++();
		CollectionIterator operator++(int);
		friend bool operator==(const CollectionIterator& a, const CollectionIterator& b);
		friend bool operator!=(const CollectionIterator& a, const CollectionIterator& b);

	protected:
		Resource m_Current;
		std::string m_RootDirectory;
		std::filesystem::recursive_directory_iterator m_Iterator;
		std::filesystem::recursive_directory_iterator m_End;

		void UpdateCurrent();
		virtual void IterateToNextValidResource();
	};
	
	class Collection
	{
	public:
		Collection(std::string rootDirectory);
		std::string GetRootDirectory() const;
		CollectionIterator begin();
		CollectionIterator end();

	private:
		std::string m_RootDirectory;
	};
}

