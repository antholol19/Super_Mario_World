#pragma once
#include "SDL.h"
#include <stdio.h>
#include <iostream>
#include "defs.h"
#include "BoxCollider2DComponent.h"
#include "TextureRectangle.h"
#include "AnimatedSprite.h"
#include "EntityManager.h"
#include "SoundComponent.h"
#include "DynamicText.h"
#include "EntityManager.h"
#include "Hero.h"
#include "Layer.h"
#include "BGSpriteComponent.h"

#include <memory>
#include <set>

class Game
{
public: 
	Game();

	void initialize();
	void loop();
	void shutDown();

	bool isRunning();
private:

	void handleEvents();
	void handleUpdate();
	void handleSound();
	void handleRendering();
	void draw();
	void loadData();

	SDL_Window* _window;
	SDL_Renderer* _renderer;
	bool _isRunning;

	Uint32 _startTime;

	std::shared_ptr<Hero> _hero;
	BGSpriteComponent* _bgSpriteComponent;
	AnimatedSprite* _animatedSprite;
	SoundComponent* _worldMusic;

	DynamicText* _text;

	static int offsetX;

	static const float SCROLLING_SPEED;
	
	std::set<SDL_TimerID> _timers;

	static Uint32 count(Uint32 interval, void* name);
	static int countValue;


};

