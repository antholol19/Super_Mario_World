#include "SpriteComponent.h"

SpriteComponent::SpriteComponent() : _texture(nullptr), _name("")
{

}

SpriteComponent::SpriteComponent(SDL_Renderer* renderer, std::string filepath)
{
	_name = "";
	SDL_Surface* surface = ResourceManager::getInstance().getSurface(filepath);
	SDL_SetColorKey(surface, SDL_FALSE, SDL_MapRGB(surface->format, 0xFF, 0x00, 0xFF));
	_texture = SDL_CreateTextureFromSurface(renderer, surface);

	// Set width/height
	SDL_QueryTexture(_texture, nullptr, nullptr, &_texWidth, &_texHeight);
}


SpriteComponent::~SpriteComponent()
{
	SDL_DestroyTexture(_texture);
}

void SpriteComponent::update(float deltaTime)
{

}

void SpriteComponent::render(SDL_Renderer* renderer)
{
	if (_texture != nullptr)
	{
		SDL_RenderCopy(renderer, _texture, &_src, &_dst);
	}
}

void SpriteComponent::setPositionDst(float x, float y)
{
	_dst.x = static_cast<int>(x);
	_dst.y = static_cast<int>(y);
}

void SpriteComponent::setDimensionDst(int w, int h)
{
	_dst.w = w;
	_dst.h = h;
}

void SpriteComponent::setFrames(int i, int j, int w, int h, int gridLineWidth)
{
	for (int row = 1; row <= i; row++)
	{
		for (int col = 1; col <= j; col++)
		{
			Frame frame = Frame(w, h);
			float posX = (gridLineWidth + w) * col - (w + gridLineWidth);
			float posY = (gridLineWidth + h) * row - (h + gridLineWidth);
			frame.setFramePosition({ posX, posY });
			_frames.push_back(frame);
		}
	}
	
}

Frame SpriteComponent::getFrame(int frameNumber)
{
	return _frames[frameNumber];
}