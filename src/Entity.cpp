#include "Entity.h"
#include "BoxCollider2DComponent.h"

Entity::Entity(std::string name)
{
	_sprite = nullptr;
	_name = name;
}


Entity::~Entity()
{
	for (int i = 0; i < _colliders.size(); i++)
	{
		delete _colliders[i];
	}

}

void Entity::update(float deltaTime)
{
	
}

void Entity::addSpriteComponent(SDL_Renderer* renderer, std::string name, Layer layer, std::string filepath)
{
	_sprite = std::make_shared<SpriteComponent>(renderer, filepath);
	_sprite->setLayer(layer);
	ComponentManager::getInstance().addComponent(name, _sprite);
}

void Entity::addCollider2DComponent()
{
	_colliders.push_back(new BoxCollider2DComponent());
}

BoxCollider2DComponent& Entity::getBoxCollider2D(size_t index)
{
	return *_colliders[index];
}

void Entity::setPosition(float x, float y)
{
	if (_sprite != nullptr)
	{
		_sprite->setPositionDst(x, y);
	}
	for (int i = 0; i < _colliders.size(); i++)
	{
		if (_colliders[i] != nullptr)
		{
			_colliders[i]->setAbsolutePosition(x, y);
		}
	}
}

void Entity::setDimensions(int w, int h)
{
	if (_sprite != nullptr)
	{
		_sprite->setDimensionDst(w, h);
	}
	for (int i = 0; i < _colliders.size(); i++)
	{
		if (_colliders[i] != nullptr)
		{
			_colliders[i]->setDimensions(w, h);
		}
	}
}