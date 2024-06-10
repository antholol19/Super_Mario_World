#pragma once
#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
#include "Entity.h"
#include <unordered_map>
#include <memory>

#include "layer.h"

class EntityManager
{
public:
	static EntityManager& getInstance();
	std::shared_ptr<Entity> createEntity(std::string name, SDL_Renderer* renderer, Layer layer);
	std::shared_ptr<Entity> getEntity(std::string name);
	void addEntity(std::shared_ptr<Entity> entity, Layer layer);
	void removeEntity(std::string name);

	void renderLayer(Layer layer);
	void renderAll();
	void updateAll(float deltaTime);
	void deleteAll();

private:
	EntityManager();
	~EntityManager();
	EntityManager(const EntityManager&);
	EntityManager operator=(const EntityManager&);

	std::unordered_map<std::string, std::shared_ptr<Entity>> _entities;
	int _entityCount;

};

#endif // ENTITY_MANAGER_H
