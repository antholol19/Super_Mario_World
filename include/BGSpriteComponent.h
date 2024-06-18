#pragma once
#ifndef BACKGROUND_SPRITE_COMPONENT_H
#define BACKGROUND_SPRITE_COMPONENT_H

#include "SpriteComponent.h"
#include "SDL.h"
#include "defs.h"
#include "ResourceManager.h"
#include "Layer.h"
#include <string>

class BGSpriteComponent : public SpriteComponent
{
public:
	BGSpriteComponent(SDL_Renderer* renderer, std::string filepath);
	~BGSpriteComponent();

	void update(float deltaTime);
	void render(SDL_Renderer* renderer);

	// Position of the frame on the grid texture
	void playBGFrame(int row, int col);

	// Get/set screen size and scroll speed
	void setTextureSize(int w, int h, float scale = 1.0);

	void setScrollSpeed(float speed) { _scrollSpeed = speed; }
	float getScrollSpeed() const { return _scrollSpeed; }
	void setOffsetX(int offsetX) { _offsetX = offsetX; }
private:
	
	float _scrollSpeed;
	int _offsetX;
	SDL_Texture* _texture;
	Layer _layer;
};

#endif // !BACKGROUND_SPRITE_COMPONENT_H
