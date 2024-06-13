#include "AnimatedSpriteComponent.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(SDL_Renderer* renderer, std::string filepath)
{
	_isFlipped = false;
	SDL_Surface* surface = ResourceManager::getInstance().getSurface(filepath);
	SDL_SetColorKey(surface, SDL_FALSE, SDL_MapRGB(surface->format, 0xFF, 0x00, 0xFF));
	_texture = SDL_CreateTextureFromSurface(renderer, surface);
	// Set width/height
	SDL_QueryTexture(_texture, nullptr, nullptr, &_texWidth, &_texHeight);
}

AnimatedSpriteComponent::AnimatedSpriteComponent(SDL_Renderer* renderer, std::string filepath, int redColorKey, int greenColorKey, int blueColorKey)
{
	_isFlipped = false;
	SDL_Surface* surface = ResourceManager::getInstance().getSurface(filepath);
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, redColorKey, greenColorKey, blueColorKey));
	_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	// Set width/height
	SDL_QueryTexture(_texture, nullptr, nullptr, &_texWidth, &_texHeight);
}

AnimatedSpriteComponent::~AnimatedSpriteComponent()
{
	SDL_DestroyTexture(_texture);
}


void AnimatedSpriteComponent::playFrame(int row, int col)
{
	// update the src position (in pixel) according to the frame found on the grid
	int frameIdx = row * col - 1;
	_src.x = _frames[frameIdx].getFramePositionX();
	_src.y = _frames[frameIdx].getFramePositionY();
	_src.w = _frames[frameIdx].getFrameWidth();
	_src.h = _frames[frameIdx].getFrameHeight();
}

void AnimatedSpriteComponent::update(float deltaTime)
{

}

void AnimatedSpriteComponent::render(SDL_Renderer* renderer)
{
	if (_texture != nullptr)
	{
		if (_isFlipped)
		{
			SDL_RenderCopyEx(renderer, _texture, &_src, &_dst, 0.0f, nullptr, SDL_FLIP_HORIZONTAL);
		}
		else
		{
			SDL_RenderCopy(renderer, _texture, &_src, &_dst);
		}
	}
	
}