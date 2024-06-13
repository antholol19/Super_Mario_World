#pragma once
#ifndef HERO_H
#define HERO_H

#include "Entity.h"
#include "defs.h"
#include "AnimatedSpriteComponent.h"
#include "ComponentManager.h"
#include <memory>

class Hero : public Entity
{
public:
	Hero(std::string name);
	~Hero();

	virtual void update(float deltaTime) override;

	void processKeyboard(const uint8_t* state);

	void addAnimatedSpriteComponent(SDL_Renderer* renderer, std::string name, Layer layer, std::string filepath, int redColorKey, int greenColorKey, int blueColorKey);
	
	// size of mario
	virtual void setDimensions(int w, int h) override;
	virtual void setPosition(float x, float y) override;
	
	// TODO: REMOVE
	void setFrames(int i, int j, int w, int h, int gridLineWidth);

private:
	std::string _name;
	std::shared_ptr<AnimatedSpriteComponent> _animSprite;
	MarioState _marioState;
	
	float _dir;
	Grid2D _framePos;

	static const float MAX_SPEED;
	void loopFrame(Grid2D firstFrame, Grid2D lastFrame);

	
};
#endif // !HERO_H
