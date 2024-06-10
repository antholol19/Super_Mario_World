#include "Entity.h"
#include "BoxCollider2DComponent.h"

Entity::Entity()
{
	_renderer = nullptr;
	_sprite = nullptr;
	_name = "NoName";
}

Entity::Entity(std::string name, SDL_Renderer* renderer)
{
	_renderer = renderer;
	_sprite = nullptr;
	_name = name;
}


Entity::~Entity()
{
	if (_sprite != nullptr)
	{
		delete _sprite;
	}
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

void Entity::render()
{
	if (nullptr != _sprite)
	{
		_sprite->render(_renderer);
	}

	for (int i = 0; i < _colliders.size(); i++)
	{
		if (nullptr != _colliders[i])
		{
			SDL_SetRenderDrawColor(_renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawRect(_renderer, &_colliders[i]->getColliderBoundingBox());
		}
	}
	
}

void Entity::addTextureRectangleComponent(std::string spritePath)
{
	_sprite = new TextureRectangle(_renderer, spritePath);
}

void Entity::addTextureRectangleComponent(std::string spritePath, int redColorKey, int greenColorKey, int blueColorKey)
{
	_sprite = new TextureRectangle(_renderer, spritePath, redColorKey, greenColorKey, blueColorKey);
}

void Entity::addCollider2DComponent()
{
	_colliders.push_back(new BoxCollider2DComponent());
}

TextureRectangle& Entity::getTextureRectangle()
{
	return *_sprite;
}

BoxCollider2DComponent& Entity::getBoxCollider2D(size_t index)
{
	return *_colliders[index];
}

void Entity::setPosition(float x, float y)
{
	if (_sprite != nullptr)
	{
		_sprite->setPosition(x, y);
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
		_sprite->setDimensions(w, h);
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