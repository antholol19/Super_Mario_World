#include "EntityManager.h"

EntityManager::EntityManager()
{

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
	static EntityManager* instance = new EntityManager();
	return *instance;
}

std::shared_ptr<Entity> EntityManager::createEntity(std::string name, SDL_Renderer* renderer, Layer layer)
{
	std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(name, renderer);
	newEntity->setLayer(layer);

	_entities.insert(std::make_pair(name, newEntity));
	_entityCount++;

	return _entities[name];
}

std::shared_ptr<Entity> EntityManager::getEntity(std::string name)
{
	return _entities[name];
}

void EntityManager::addEntity(std::shared_ptr<Entity> entity, Layer layer)
{
	entity->setLayer(layer);
	_entities.insert(std::make_pair(entity->getName(), entity));
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

void EntityManager::renderAll()
{
	renderLayer(Layer::BACKGROUND);
	renderLayer(Layer::MIDDLEGROUND);
	renderLayer(Layer::FOREGROUND);
}

void EntityManager::renderLayer(Layer layer)
{
	for (auto it = _entities.begin(); it != _entities.end(); it++)
	{
		if (it->second != nullptr)
		{
			if (layer == it->second->getLayer())
			{
				it->second->render();
			}
		}
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
}
