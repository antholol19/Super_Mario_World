#include "Game.h"
#include <cstdlib>
#include <memory>

int Game::offsetX = 0; // Allow to scroll in the x direction
int Game::countValue = 0;
const float Game::SCROLLING_SPEED = 0.2f;
Game::Game() : _window(nullptr), _renderer(nullptr), _isRunning(false)
{
	_bgSpriteComponent = nullptr;
	_worldMusic = nullptr;
	_text = nullptr;
}

void Game::initialize()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}

	// Create Window
	_window = SDL_CreateWindow("BricksBreaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!_window)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (!_renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
	loadData();
	_startTime = SDL_GetTicks();
	_isRunning = true;
}

void Game::loop()
{
	while (_isRunning) 
	{ 
		handleEvents();
		handleUpdate();
		handleSound();
		handleRendering();
	}
}

void Game::shutDown()
{
	delete _worldMusic;
	delete _text;
	EntityManager::getInstance().deleteAll();
	std::set<SDL_TimerID>::iterator it;
	for (it = _timers.begin(); it != _timers.end(); it++)
	{
		SDL_RemoveTimer(*it);
	}

	//Destroy window
	SDL_DestroyWindow(_window);

	//Quit SDL subsystems
	SDL_Quit();
}

bool Game::isRunning()
{
	return _isRunning;
}

void Game::handleEvents()
{
	//Hack to get window to stay up
	SDL_Event e;
	
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			_isRunning = false;
			break;
		default:
			
			break;
		}
	}
	
	// return pointer to keys
	const Uint8* pKeys = SDL_GetKeyboardState(NULL);
	_hero->processKeyboard(pKeys);

	// Handle tile input
	if (pKeys[SDL_SCANCODE_D])
	{
		--offsetX;
	}
	if (pKeys[SDL_SCANCODE_A])
	{
		offsetX++;
	}
	if (offsetX * SCROLLING_SPEED < -SCREEN_WIDTH || offsetX * SCROLLING_SPEED > SCREEN_WIDTH)
	{
		offsetX = 0;
	}

	_bgSpriteComponent->setOffsetX(offsetX);
}

void Game::handleUpdate()
{
	Uint32 elapsedTime = SDL_GetTicks() - _startTime;
	Uint32 framePerSec = 60;
	Uint32 frameRate = 1 / framePerSec * 1000;

	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), _startTime + frameRate))
		;

	float deltaTime = (SDL_GetTicks() - _startTime) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	_startTime = SDL_GetTicks();

	EntityManager::getInstance().updateAll(deltaTime);
	_bgSpriteComponent->setPositionDst(_hero->getPosition().x, _hero->getPosition().y);
	ComponentManager::getInstance().updateAll(deltaTime);
	
}

void Game::handleSound()
{
	
}

void Game::handleRendering()
{
	SDL_SetRenderDrawColor(_renderer, 96, 128, 255, 255);
	SDL_RenderClear(_renderer);

	ComponentManager::getInstance().renderAll(_renderer);
	_text->drawText(_renderer, std::to_string(countValue), 700, 10, 100, 100);
	SDL_RenderPresent(_renderer);
}
	
	

void Game::draw()
{
	
}

void Game::loadData()
{
	// create entities
	//EntityManager::getInstance().createEntity("stage", Layer::MIDDLEGROUND);


	_hero = std::make_shared<Hero>("hero");
	_hero->addAnimatedSpriteComponent(_renderer, "small_mario", Layer::FOREGROUND, "./assets/images/small_mario.bmp", 0x00, 0x74, 0x74);
	_hero->setFrames(5, 16, 48, 48, 1);
	_hero->setPosition(50.0f, 200.0f);
	_hero->setDimensions(100, 100);
	EntityManager::getInstance().addEntity(_hero);
	

	/*
	std::shared_ptr<Entity> stage = EntityManager::getInstance().getEntity("stage");
	stage->addSpriteComponent(_renderer, "./assets/images/SNES-Super_Mario_World_Yoshis_Island_2.bmp");
	stage->setPosition(500.0f, 500.0f);
	stage->setDimensions(10000, 500);
	*/

	_bgSpriteComponent = std::make_shared<BGSpriteComponent>(_renderer, "./assets/images/background_super_mario_world.bmp");
	_bgSpriteComponent->setLayer(Layer::BACKGROUND);
	_bgSpriteComponent->setTextureSize(SCREEN_WIDTH, SCREEN_HEIGHT, 1);
	_bgSpriteComponent->setFrames(7, 4, 512, 432, 1);
	_bgSpriteComponent->playBGFrame(2, 4);
	_bgSpriteComponent->setScrollSpeed(SCROLLING_SPEED);
	ComponentManager::getInstance().addComponent("background", _bgSpriteComponent);

	_worldMusic = new SoundComponent("./assets/sounds/Overworld Theme - Super Mario World.wav");
	_worldMusic->setupDevice();
	_worldMusic->playSound();


	// text
	_text = new DynamicText("./assets/fonts/8bitOperatorPlus8-Regular.ttf", 32);

	// add timer
	SDL_TimerID timerId = SDL_AddTimer(1000, count, this);
	_timers.insert(timerId);

}

Uint32 Game::count(Uint32 interval, void* param)
{
	countValue++; // each second, increment by 1 
	SDL_Event event;
	SDL_UserEvent userevent;

	/* In this example, our callback pushes an SDL_USEREVENT event
	into the queue, and causes our callback to be called again at the
	same interval: */

	// Create looping 
	userevent.type = SDL_USEREVENT;
	userevent.code = 0;
	userevent.data1 = NULL;
	userevent.data2 = NULL;

	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);
	return(interval);
	
}