#pragma once
#ifndef DYNAMIC_TEXT_H
#define DYNAMIC_TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
class DynamicText
{
public:
	DynamicText(std::string filepath, size_t fontSize);
	~DynamicText();

	void drawText(SDL_Renderer* renderer, std::string text, int x, int y, int w, int h);

private:
	static bool _ttfInitialized;

	TTF_Font* _font;
	SDL_Texture* _textureText;
	SDL_Rect _rect;
};

#endif // !DYNAMIC_TEXT_H