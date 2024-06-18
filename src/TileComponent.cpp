#include "TileComponent.h"
#include "EntityManager.h"
#include "defs.h"

TileComponent::TileComponent(int id, SDL_Texture* texture, SDL_Rect& src, SDL_Rect& dst) : _id(id), _texture(texture)
{
	_pos.x = static_cast<float>(dst.x); 
	_pos.y = static_cast<float>(dst.y);
	_src = src;
	_dst = dst;
	_layer = Layer::MIDDLEGROUND;
}

TileComponent::~TileComponent()
{

}

void TileComponent::update(float deltaTime)
{
	if (EntityManager::getInstance().getEntity("hero")->getPosition().x >= (SCREEN_WIDTH / 2 - 200))
	{

		_pos.x += EntityManager::getInstance().getEntity("hero")->getVelocity().x * deltaTime * (-1);
		_pos.y += EntityManager::getInstance().getEntity("hero")->getVelocity().y * deltaTime * (-1);
		_dst.x = static_cast<int>(_pos.x);
		_dst.y = static_cast<int>(_pos.y);
	}
	
}

void TileComponent::render(SDL_Renderer* renderer)
{
	if (_texture != nullptr)
	{
		SDL_RenderCopy(renderer, _texture, &_src, &_dst);
	}
}
