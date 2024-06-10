#include "BGSpriteComponent.h"
BGSpriteComponent::BGSpriteComponent(SDL_Renderer* renderer, std::string filepath)
{
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
	
}

void BGSpriteComponent::render(SDL_Renderer* renderer)
{
	if (_texture != nullptr)
	{
		SDL_Rect r;
		// TODO: multiply texture dimension by a scale
		r.w = _screenSize.x;
		r.h = _screenSize.y;
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(_offsetX * _scrollSpeed);
		r.y = 0;
		SDL_RenderCopy(renderer, _texture, &_src, &r);
		if (_offsetX < 0)
		{
			r.x = static_cast<int>(_offsetX * _scrollSpeed + _screenSize.x);
		}
		else
		{
			r.x = static_cast<int>(_offsetX * _scrollSpeed - _screenSize.x);
		}
		
		SDL_RenderCopy(renderer, _texture, &_src, &r);
	}
	
}

void BGSpriteComponent::playBGFrame(int frame)
{
	// update the src position (in pixel) according to the frame found on the grid
	int col;
	int row;

	if (frame % _frameElement.x == 0)
	{
		col = _frameElement.x;
		row = frame / _frameElement.x;
	}
	else
	{
		col = frame % _frameElement.x;
		row = frame / _frameElement.x + 1;
	}

	_src.x = (1 + _src.w) * col - (_src.w + 1);
	_src.y = (1 + _src.h) * row - (_src.h + 1);
}

void BGSpriteComponent::setImageGridSize(int row, int col)
{
	_frameElement.x = row;
	_frameElement.y = col;
}

void BGSpriteComponent::setFrameDimension(int w, int h)
{
	_src.w = w;
	_src.h = h;
}

void BGSpriteComponent::setPosition(const Vec2D& pos)
{
	_pos = pos;
}