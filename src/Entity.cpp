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
	/*
	if (nullptr != _sprite)
	{
		int x = _sprite->getXPosition();
		int y = _sprite->getYPosition();
		int w = _sprite->getWidth();
		int h = _sprite->getHeight();
		
	}
	*/
}

void Entity::render(SDL_Renderer* renderer)
{
	if (nullptr != _sprite)
	{
		_sprite->render(renderer);
	}

	for (int i = 0; i < _colliders.size(); i++)
	{
		if (nullptr != _colliders[i])
		{
			SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawRect(renderer, &_colliders[i]->getColliderBoundingBox());
		}
	}
	
}

void Entity::addSpriteComponent(SDL_Renderer* renderer, std::string filepath)
{
	_sprite = std::make_shared<SpriteComponent>(renderer, filepath);
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

void Entity::setLayer(Layer layer)
{
	_layer = layer;
}

Layer Entity::getLayer() 
{
	return _layer;
}