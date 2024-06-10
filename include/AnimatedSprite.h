#pragma once
#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <SDL.h>
#include <string>
#include "ResourceManager.h"
#include "defs.h"

class AnimatedSprite
{
public:
	AnimatedSprite(SDL_Renderer* renderer, std::string filepath);
	AnimatedSprite(SDL_Renderer* renderer, std::string filepath, int redColorKey, int greenColorKey, int blueColorKey);

	~AnimatedSprite();

	// play the corresponding frame
	void playFrame(int frame);

	void update();

	void render(SDL_Renderer* renderer, bool isFlipped = false);

	// sprite position and size when rendered
	void setPositionDst(float x, float y);
	void setDimensionDst(int w, int h);
	
	void setImageGridSize(int i, int j);

	// Size of the frame (src)
	void setFrameDimension(int w, int h);
private:

	SDL_Rect _src;
	SDL_Rect _dst;
	SDL_Texture* _texture;
	Vec2DInt _frameElement;

};
#endif // !ANIMATED_SPRITE_H

