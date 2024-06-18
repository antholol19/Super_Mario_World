#include "ResourceManager.h"
ResourceManager* ResourceManager::_instance = nullptr;
ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	for (auto itr = _surfaces.begin(); itr != _surfaces.end(); itr++)
	{
		SDL_FreeSurface(itr->second);
	}
}

ResourceManager::ResourceManager(const ResourceManager&)
{

}

ResourceManager ResourceManager::operator=(const ResourceManager&)
{
	// Not needed
	return *this;
}

ResourceManager& ResourceManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new ResourceManager();
	}
	return *_instance;
}

SDL_Surface* ResourceManager::getSurface(std::string filepath)
{
	// find the file
	auto it = _surfaces.find(filepath);
	if (it == _surfaces.end())
	{
		// surface not found, Load bitmap image onto an SDL Surface
		SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
		if (surface == NULL)
		{
			printf("Unable to load image %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError());
		}
		else
		{
			_surfaces.insert(std::make_pair(filepath, surface));
		}
		
	}
	
	return _surfaces[filepath];
}
