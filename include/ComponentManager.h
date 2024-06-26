#pragma once
#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include "SDL.h"
#include <unordered_map>
#include <string>
#include <memory>
#include "Component.h"
#include "SpriteComponent.h"
#include "TileComponent.h"
#include "Layer.h"

class ComponentManager
{
public:
	static ComponentManager& getInstance();

	void addComponent(std::string name, std::shared_ptr<Component> component);
	void removeComponent(std::string name);

	void addTileComponent(int id, SDL_Texture* texture, SDL_Rect& src, SDL_Rect& dst);

	std::shared_ptr<Component> getComponent(std::string name);

	void renderLayer(SDL_Renderer* renderer, Layer layer);
	void renderAll(SDL_Renderer* renderer);
	void updateAll(float deltaTime);
	void deleteAll();

private:
	ComponentManager();
	~ComponentManager();
	ComponentManager(const ComponentManager&);
	ComponentManager operator=(const ComponentManager&);
	static ComponentManager* _instance;
	std::unordered_map<std::string, std::shared_ptr<Component>> _components;
	std::vector<std::shared_ptr<TileComponent>> _tileComponents;
	int _componentCount;
};
#endif // !COMPONENT_MANAGER_H
