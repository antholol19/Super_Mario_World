#pragma once
#ifndef BACKGROUND_SPRITE_COMPONENT_H
#define BACKGROUND_SPRITE_COMPONENT_H

#include "SDL.h"
#include "defs.h"
#include "ResourceManager.h"
#include "Layer.h"
#include <string>

class BGSpriteComponent
{
public:
	BGSpriteComponent(SDL_Renderer* renderer, std::string filepath);
	~BGSpriteComponent();

	void update(float deltaTime);
	void render(SDL_Renderer* renderer);

	void playBGFrame(int frame);

	void setImageGridSize(int row, int col);
	void setFrameDimension(int w, int h);

	// Get/set screen size and scroll speed
	void setScreenSize(const Vec2DInt& size) { _screenSize = size; }
	// set the position of the texture according to the position of the hero
	void setPosition(const Vec2D& pos);
	void setScrollSpeed(float speed) { _scrollSpeed = speed; }
	float getScrollSpeed() const { return _scrollSpeed; }
	void setOffsetX(int offsetX) { _offsetX = offsetX; }
private:
	
	float _scrollSpeed;
	int _offsetX;
	SDL_Texture* _texture;
	SDL_Rect _src;
	Vec2D _pos;
	Vec2DInt _screenSize;
	Vec2DInt _frameSize;
	Vec2DInt _frameElement;
	Layer _layer;
};

#endif // !BACKGROUND_SPRITE_COMPONENT_H
