#pragma once
#ifndef HERO_H
#define HERO_H

#include "Entity.h"
#include "defs.h"
#include "AnimatedSprite.h"
class Hero : public Entity
{
public:
	Hero(std::string name, SDL_Renderer* renderer);
	~Hero();
	virtual void render() override;
	virtual void update(float deltaTime) override;
	void processKeyboard(const uint8_t* state);

	void addAnimatedSpriteComponent(SDL_Renderer* renderer, std::string filepath, int redColorKey, int greenColorKey, int blueColorKey);
	
	// size of mario
	virtual void setDimensions(int w, int h) override;
	virtual void setPosition(float x, float y) override;
	
	// size of the frame
	void setFrameDimension(int w, int h);
	void setImageGridSize(int i, int j);

private:
	AnimatedSprite* _animSprite;
	MarioState _marioState;
	
	float _dir;
	int _frameNumber;

	static const float MAX_SPEED;
	void loopFrame(int firstFrame, int lastFrame);

	
};
#endif // !HERO_H
