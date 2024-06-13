#pragma once
#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "layer.h"
#include <unordered_map>
#include <string>
#include <memory>

class EntityManager
{
public:
	static EntityManager& getInstance();
	std::shared_ptr<Entity>& createEntity(std::string name);
	std::shared_ptr<Entity>& getEntity(std::string name);
	void addEntity(const std::shared_ptr<Entity>& entity);
	void removeEntity(std::string name);

	void updateAll(float deltaTime);
	void deleteAll();

private:
	EntityManager();
	~EntityManager();
	EntityManager(const EntityManager&);
	EntityManager operator=(const EntityManager&);
	static EntityManager* _instance;
	std::unordered_map<std::string, std::shared_ptr<Entity>> _entities;
	int _entityCount;

};

#endif // ENTITY_MANAGER_H
