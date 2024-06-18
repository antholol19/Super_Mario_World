#include "ComponentManager.h"

ComponentManager* ComponentManager::_instance = nullptr;
ComponentManager::ComponentManager() 
{
	_componentCount = 0;
}

ComponentManager::~ComponentManager()
{

}

ComponentManager& ComponentManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new ComponentManager();
	}
	return *_instance;
}

void ComponentManager::addComponent(std::string name, std::shared_ptr<Component> component)
{
	// TODO: maybe insert the component according to the drawing order
	component->setName(name);
	auto it = _components.find(name);
	if (it == _components.end())
	{
		_components.insert(std::make_pair(name, component));
		_componentCount++;
	}
	else
	{
		SDL_Log("This component already exist");
	}
	
}

void ComponentManager::removeComponent(std::string name)
{
	auto it = _components.find(name);
	if (it != _components.end())
	{
		_components.erase(it);
		_componentCount--;
	}
}

void ComponentManager::addTileComponent(int id, SDL_Texture* texture, SDL_Rect& src, SDL_Rect& dst)
{
	_tileComponents.push_back(std::make_shared<TileComponent>(id, texture, src, dst));
}

std::shared_ptr<Component> ComponentManager::getComponent(std::string name)
{
	return _components[name];
}

void ComponentManager::renderAll(SDL_Renderer* renderer)
{
	renderLayer(renderer, Layer::BACKGROUND);
	renderLayer(renderer, Layer::MIDDLEGROUND);
	renderLayer(renderer, Layer::FOREGROUND);
}

void ComponentManager::renderLayer(SDL_Renderer* renderer, Layer layer)
{
	// use dynamic pointer cast on components to render only those with a render method
	if (layer == Layer::MIDDLEGROUND)
	{
		for (auto e : _tileComponents)
		{
			e->render(renderer);
		}
	}
	for (auto it = _components.begin(); it != _components.end(); it++)
	{
		std::shared_ptr<SpriteComponent> sprite = std::dynamic_pointer_cast<SpriteComponent>(it->second);
		if (sprite)
		{
			if (layer == sprite->getLayer())
			{
				sprite->render(renderer);
			}
		}
	}
	
}

void ComponentManager::updateAll(float deltaTime)
{
	for (auto e : _tileComponents)
	{
		e->update(deltaTime);
	}
	for (auto it = _components.begin(); it != _components.end(); it++)
	{
		if (it->second != nullptr)
		{
			it->second->update(deltaTime);
		}
	}
}


void ComponentManager::deleteAll()
{
	_components.erase(_components.begin(), _components.end());
	_componentCount = 0;
}