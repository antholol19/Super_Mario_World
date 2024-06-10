#include "TextureRectangle.h"

TextureRectangle::TextureRectangle(SDL_Renderer* renderer, std::string filepath)
{
	SDL_Surface* surface = ResourceManager::getInstance().getSurface(filepath);
	SDL_SetColorKey(surface, SDL_FALSE, SDL_MapRGB(surface->format, 0xFF, 0x00, 0xFF));
	_texture = SDL_CreateTextureFromSurface(renderer, surface);

	// default
	_rect.x = 0;
	_rect.y = 0;
	_rect.w = 32;
	_rect.h = 32;

	_redColorKey = 0xFF;
	_greenColorKey = 0x00;
	_blueColorKey = 0xFF;
}

TextureRectangle::TextureRectangle(SDL_Renderer* renderer, std::string filepath, int redColorKey, int greenColorKey, int blueColorKey)
{
	SDL_Surface* surface = ResourceManager::getInstance().getSurface(filepath);

	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, redColorKey, greenColorKey, blueColorKey));
	_texture = SDL_CreateTextureFromSurface(renderer, surface);

	defaultInit();
	
	_redColorKey = redColorKey;
	_greenColorKey = greenColorKey;
	_blueColorKey = blueColorKey;
}

TextureRectangle::~TextureRectangle()
{
	SDL_DestroyTexture(_texture);
}

void TextureRectangle::defaultInit()
{
	// default
	_rect.x = 0;
	_rect.y = 0;
	_rect.w = 32;
	_rect.h = 32;

	_redColorKey = 0xFF;
	_greenColorKey = 0x00;
	_blueColorKey = 0xFF;
}

void TextureRectangle::update()
{

}

void TextureRectangle::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, _texture, NULL, &_rect);
}

void TextureRectangle::setPosition(int x, int y)
{
	_rect.x = x;
	_rect.y = y;
}

void TextureRectangle::setDimensions(int w, int h)
{
	_rect.w = w;
	_rect.h = h;
}

int TextureRectangle::getPosX()
{
	return _rect.x;
}

int TextureRectangle::getPosY()
{
	return _rect.y;
}

int TextureRectangle::getWidth()
{
	return _rect.w;
}

int TextureRectangle::getHeight()
{
	return _rect.h;
}
