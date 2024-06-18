#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SDL.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

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
	static ResourceManager* _instance;
	std::unordered_map<std::string, SDL_Surface*> _surfaces;
	std::vector<std::shared_ptr<SDL_Texture>> _tiles;

};
#endif // RESSOURCE_MANAGER_H

