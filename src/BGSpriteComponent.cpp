#include "BGSpriteComponent.h"
BGSpriteComponent::BGSpriteComponent(SDL_Renderer* renderer, std::string filepath)
{
	_name = "";
	_scrollSpeed = 0.0f;
	SDL_Surface* surface = ResourceManager::getInstance().getSurface(filepath);
	_texture = SDL_CreateTextureFromSurface(renderer, surface);
	_layer = Layer::BACKGROUND;
}

BGSpriteComponent::~BGSpriteComponent()
{
	SDL_DestroyTexture(_texture);
}

void BGSpriteComponent::update(float deltaTime)
{
	if (_offsetX < 0)
	{
		_dst.x = static_cast<int>(_offsetX * _scrollSpeed + _dst.w);
	}
	else
	{
		_dst.x = static_cast<int>(_offsetX * _scrollSpeed - _dst.w);
	}
	
}

void BGSpriteComponent::render(SDL_Renderer* renderer)
{
	if (_texture != nullptr)
	{	
		SDL_RenderCopy(renderer, _texture, &_src, &_dst);
		_dst.x = static_cast<int>(_offsetX * _scrollSpeed);
		SDL_RenderCopy(renderer, _texture, &_src, &_dst);

	}
}

void BGSpriteComponent::playBGFrame(int row, int col)
{
	// update the src position (in pixel) according to the frame found on the grid
	int frameIdx = row * col - 1;
	_src.x = _frames[frameIdx].getFramePositionX();
	_src.y = _frames[frameIdx].getFramePositionY();
	_src.w = _frames[frameIdx].getFrameWidth();
	_src.h = _frames[frameIdx].getFrameHeight();
}

void BGSpriteComponent::setTextureSize(int w, int h, float scale)
{
	_dst.w = static_cast<int>(w * scale);
	_dst.h = static_cast<int>(h * scale);
}