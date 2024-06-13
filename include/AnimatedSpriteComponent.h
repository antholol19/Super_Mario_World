#pragma once
#ifndef ANIMATED_SPRITE_COMPONENT_H
#define ANIMATED_SPRITE_COMPONENT_H

#include "SpriteComponent.h"
#include <SDL.h>
#include <string>
#include "ResourceManager.h"
#include "defs.h"

class AnimatedSpriteComponent : public SpriteComponent
{
public:
	AnimatedSpriteComponent(SDL_Renderer* renderer, std::string filepath);
	AnimatedSpriteComponent(SDL_Renderer* renderer, std::string filepath, int redColorKey, int greenColorKey, int blueColorKey);

	~AnimatedSpriteComponent();

	virtual void update(float deltaTime) override;
	virtual void render(SDL_Renderer* renderer) override;

	// play the corresponding frame
	void playFrame(int row, int col);
	

	void setIsFlipped(bool isFlipped) { _isFlipped = isFlipped; }
private:
	bool _isFlipped;
	SDL_Texture* _texture;
	int _texWidth;
	int _texHeight;

};
#endif // !ANIMATED_SPRITE_COMPONENT_H

