#include "Game.h"
#include <cstdlib>
#include <memory>

int Game::offsetX = 0; // Allow to scroll in the x direction
int Game::countValue = 0;
const float Game::SCROLLING_SPEED = 0.2f;
Game::Game() : _window(nullptr), _renderer(nullptr), _isRunning(false)
{
	_bgSpriteComponent = nullptr;
	_animatedSprite = nullptr;
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
	delete _animatedSprite;
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

		if (e.button.button == SDL_BUTTON_LEFT)
		{
			std::shared_ptr<Entity> test1 = EntityManager::getInstance().getEntity("test1");
			std::shared_ptr<Entity> test2 = EntityManager::getInstance().getEntity("test2");
			if (test2->getBoxCollider2D(0).isColliding(test1->getBoxCollider2D(0)))
			{
				std::cout << "isColliding" << std::endl;
			}
			else
			{
				std::cout << "is not colliding" << std::endl;
			}
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
	std::shared_ptr<Entity> test1 = EntityManager::getInstance().getEntity("test1");
	test1->getBoxCollider2D(0).setAbsolutePosition(test1->getTextureRectangle().getPosX(), test1->getTextureRectangle().getPosY());
	test1->getBoxCollider2D(0).setDimensions(test1->getTextureRectangle().getWidth(), test1->getTextureRectangle().getHeight() / 2);

	test1->getBoxCollider2D(1).setAbsolutePosition(test1->getTextureRectangle().getPosX(), test1->getTextureRectangle().getPosY() + 20);
	test1->getBoxCollider2D(1).setDimensions(test1->getTextureRectangle().getWidth(), test1->getTextureRectangle().getHeight() / 2);

	std::shared_ptr<Entity> test2 = EntityManager::getInstance().getEntity("test2");
	test2->getBoxCollider2D(0).setAbsolutePosition(test2->getTextureRectangle().getPosX(), test2->getTextureRectangle().getPosY());
	test2->getBoxCollider2D(0).setDimensions(test2->getTextureRectangle().getWidth(), test2->getTextureRectangle().getHeight());

	EntityManager::getInstance().updateAll(deltaTime);
	_bgSpriteComponent->setPosition(EntityManager::getInstance().getEntity("hero")->getPosition());
	
}

void Game::handleSound()
{
	
}

void Game::handleRendering()
{
	SDL_SetRenderDrawColor(_renderer, 96, 128, 255, 255);
	SDL_RenderClear(_renderer);

	_bgSpriteComponent->render(_renderer);
	EntityManager::getInstance().renderAll();
	_text->drawText(_renderer, std::to_string(countValue), 700, 10, 100, 100);
	SDL_RenderPresent(_renderer);
}
	
	

void Game::draw()
{
	
}

void Game::loadData()
{
	// create entities
	EntityManager::getInstance().createEntity("test1", _renderer, Layer::MIDDLEGROUND);
	EntityManager::getInstance().createEntity("test2", _renderer, Layer::MIDDLEGROUND);
	EntityManager::getInstance().createEntity("stage", _renderer, Layer::MIDDLEGROUND);


	_hero = std::make_shared<Hero>("hero", _renderer);
	EntityManager::getInstance().addEntity(_hero, Layer::FOREGROUND);
	_hero->addAnimatedSpriteComponent(_renderer, "./assets/images/small_mario.bmp", 0x00, 0x74, 0x74);
	_hero->setFrameDimension(48, 48);
	_hero->setImageGridSize(16, 5);
	_hero->setPosition(50.0f, 200.0f);
	_hero->setDimensions(100, 100);
	
	std::shared_ptr<Entity> test1 = EntityManager::getInstance().getEntity("test1");
	test1->addTextureRectangleComponent("./assets/images/test.bmp", 0xFF, 0x00, 0xFF);
	test1->addCollider2DComponent();
	test1->addCollider2DComponent();
	test1->setPosition(20.0f, 500.0f);
	test1->setDimensions(200, 200);

	std::shared_ptr<Entity> test2 = EntityManager::getInstance().getEntity("test2");
	test2->addTextureRectangleComponent("./assets/images/test.bmp", 0xFF, 0x00, 0xFF);
	test2->addCollider2DComponent();
	test2->setPosition(500.0f, 500.0f);
	test2->setDimensions(200, 200);

	std::shared_ptr<Entity> stage = EntityManager::getInstance().getEntity("stage");
	stage->addTextureRectangleComponent("./assets/images/SNES-Super_Mario_World_Yoshis_Island_2.bmp");
	test2->setPosition(500.0f, 500.0f);
	test2->setDimensions(10000, 500);

	_bgSpriteComponent = new BGSpriteComponent(_renderer, "./assets/images/background_super_mario_world.bmp");
	_bgSpriteComponent->setScreenSize({ SCREEN_WIDTH, SCREEN_HEIGHT });
	_bgSpriteComponent->setFrameDimension(512, 432);
	_bgSpriteComponent->setImageGridSize(4, 7);
	_bgSpriteComponent->playBGFrame(8);
	_bgSpriteComponent->setScrollSpeed(SCROLLING_SPEED);

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