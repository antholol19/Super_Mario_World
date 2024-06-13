#include "EntityManager.h"
EntityManager* EntityManager::_instance = nullptr;
EntityManager::EntityManager()
{
	_entityCount = 0;
}

EntityManager::EntityManager(const EntityManager&)
{

}

EntityManager::~EntityManager()
{

}

EntityManager EntityManager::operator=(const EntityManager&)
{
	// Not needed
	return *this;
}

EntityManager& EntityManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new EntityManager();
	}
	return *_instance;
}

std::shared_ptr<Entity>& EntityManager::createEntity(std::string name)
{
	std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(name);

	_entities.insert(std::make_pair(name, newEntity));
	_entityCount++;

	return _entities[name];
}

std::shared_ptr<Entity>& EntityManager::getEntity(std::string name) 
{
	return _entities[name];
}

void EntityManager::addEntity(const std::shared_ptr<Entity>& entity)
{
	_entities.insert(std::make_pair(entity->getName(), entity));
	_entityCount++;
}

void EntityManager::removeEntity(std::string name)
{
	auto it = _entities.find(name);
	if (it != _entities.end())
	{
		_entities.erase(it);
		_entityCount--;
	}
}

void EntityManager::updateAll(float deltaTime)
{
	for (auto it = _entities.begin(); it != _entities.end(); it++)
	{
		if (it->second != nullptr)
		{
			it->second->update(deltaTime);
		}
	}
}

void EntityManager::deleteAll()
{
	_entities.erase(_entities.begin(), _entities.end());
	_entityCount = 0;
}
