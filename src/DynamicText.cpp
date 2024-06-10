#include "DynamicText.h"
#include <stdio.h>

bool DynamicText::_ttfInitialized = false;
DynamicText::DynamicText(std::string filepath, size_t fontSize) : _textureText(nullptr)
{
	if (!_ttfInitialized && TTF_Init() == -1)
	{
		printf("SDL could not initialize True Type Font! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}
	_ttfInitialized = true;

	_font = TTF_OpenFont(filepath.c_str(), fontSize);
	if (_font == nullptr)
	{
		printf("SDL could not load Font! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

}

DynamicText::~DynamicText()
{
	SDL_DestroyTexture(_textureText);
	TTF_CloseFont(_font);
}

void DynamicText::drawText(SDL_Renderer* renderer, std::string text, int x, int y, int w, int h)
{
	SDL_Surface* surfaceText = TTF_RenderText_Solid(_font, text.c_str(), {255, 255, 255});
	_textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);
	SDL_FreeSurface(surfaceText);

	_rect.x = x;
	_rect.y = y;
	_rect.w = w;
	_rect.h = h;
	SDL_RenderCopy(renderer, _textureText, NULL, &_rect);
	SDL_DestroyTexture(_textureText);
}