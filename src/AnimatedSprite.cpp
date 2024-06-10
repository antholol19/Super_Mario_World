#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(SDL_Renderer* renderer, std::string filepath)
{
	SDL_Surface* surface = ResourceManager::getInstance().getSurface(filepath);
	SDL_SetColorKey(surface, SDL_FALSE, SDL_MapRGB(surface->format, 0xFF, 0x00, 0xFF));
	_texture = SDL_CreateTextureFromSurface(renderer, surface);
}

AnimatedSprite::AnimatedSprite(SDL_Renderer* renderer, std::string filepath, int redColorKey, int greenColorKey, int blueColorKey)
{
	SDL_Surface* surface = ResourceManager::getInstance().getSurface(filepath);
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, redColorKey, greenColorKey, blueColorKey));
	_texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	_frameElement = { 1, 1 };
}

AnimatedSprite::~AnimatedSprite()
{
	SDL_DestroyTexture(_texture);
}


void AnimatedSprite::playFrame(int frame)
{
	// update the src position (in pixel) according to the frame found on the grid
	int col = frame % _frameElement.x;
	int row = frame / _frameElement.x + 1;
	_src.x = (1 + _src.w) * col - (_src.w + 1); 
	_src.y = (1 + _src.h) * row - (_src.h + 1);
}

void AnimatedSprite::update()
{

}

void AnimatedSprite::render(SDL_Renderer* renderer, bool isFlipped)
{
	if (isFlipped)
	{
		SDL_RenderCopyEx(renderer, _texture, &_src, &_dst, 0.0f, nullptr, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		SDL_RenderCopy(renderer, _texture, &_src, &_dst);
	}
}

void AnimatedSprite::setPositionDst(float x, float y)
{
	_dst.x = static_cast<int>(x);
	_dst.y = static_cast<int>(y);
}

void AnimatedSprite::setDimensionDst(int w, int h)
{
	_dst.w = w;
	_dst.h = h;
}

void AnimatedSprite::setImageGridSize(int i, int j)
{
	_frameElement.x = i;
	_frameElement.y = j;
}

void AnimatedSprite::setFrameDimension(int w, int h)
{
	_src.w = w;
	_src.h = h;
}