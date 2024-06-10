#pragma once
#include <string>
#include <SDL.h>
#include "ResourceManager.h"

class TextureRectangle
{
public:
	// Constructor
	//TextureRectangle();
	TextureRectangle(SDL_Renderer* renderer, std::string filepath);
	TextureRectangle(SDL_Renderer* renderer, std::string filepath, int redColorKey, int greenColorKey, int blueColorKey);

	// Destructor
	~TextureRectangle();

	void defaultInit();

	void setPosition(int x, int y);
	void setDimensions(int w, int h);
	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();


	void update();

	void render(SDL_Renderer* renderer);

private:

	inline SDL_Rect getRectangle() const { return _rect; }
	SDL_Texture* _texture;
	SDL_Rect _rect;

	int _redColorKey;
	int _greenColorKey;
	int _blueColorKey;

	
};

