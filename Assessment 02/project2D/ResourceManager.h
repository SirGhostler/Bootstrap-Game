#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include "Resource.h"

template < class T >
class ResourceManager
{
	std::vector< std::shared_ptr<Resource<T>> > m_resources;

	// keep the copy constructor and assignment allocator private
	ResourceManager(const ResourceManager&) {}
	ResourceManager& operator=(const ResourceManager&) {}

public:
	// Constructor
	ResourceManager() {}
	// De-Constructor
	~ResourceManager() {}

	// Obtain Texture/Image (Image)
	std::shared_ptr<Resource<T>> get(const std::string filename) 
	{
		std::vector< std::shared_ptr<Resource<T>> >::iterator it;
		for (it = m_resources.begin(); it != m_resources.end(); it++)
		{
			if (filename.compare((*it)->getFilename()) == 0)
			{
				return (*it);
			}
		}
		std::shared_ptr<Resource<T>> resource(new Resource<T>(filename));
		m_resources.push_back(resource);
		return resource;
	}

	// Obtain Font (Font, Size)
	std::shared_ptr<Resource<T>> get(const std::string filename, int size)
	{
		std::vector< std::shared_ptr<Resource<T>> >::iterator it;
		for (it = m_resources.begin(); it != m_resources.end(); it++)
		{
			if (filename.compare((*it)->getFilename()) == 0)
			{
				return (*it);
			}
		}
		std::shared_ptr<Resource<T>> resource(new Resource<T>(filename, size));
		m_resources.push_back(resource);
		return resource;
	}

	int getCount()
	{
		return m_resources.size();
	}

	void collectGarbage()
	{
		for (std::vector< std::shared_ptr<Resource<T>> >::iterator it = m_resources.begin(); it != m_resources.end(); )
		{
			if ((*it).use_count() == 1) it = m_resources.erase(it);
			else ++it;
		}
	}
};