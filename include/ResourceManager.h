#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SDL.h>
#include <string>
#include <unordered_map>

class ResourceManager
{
public:
	~ResourceManager();
	static ResourceManager& getInstance();
	SDL_Surface* getSurface(std::string filepath);
private:
	ResourceManager();
	ResourceManager(const ResourceManager&);
	ResourceManager operator=(const ResourceManager&);

	std::unordered_map<std::string, SDL_Surface*> _surfaces;

};
#endif // RESSOURCE_MANAGER_H

