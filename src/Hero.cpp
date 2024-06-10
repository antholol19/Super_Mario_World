#include "Hero.h"
const float Hero::MAX_SPEED = 162.0f;
Hero::Hero(std::string name, SDL_Renderer* renderer) : Entity(name, renderer)
{
	_animSprite = nullptr;
	_frameNumber = 1;
	_marioState = SMALL_IDLE;
	_pos = { 0.0f, 0.0f };
	_vel = { 0.0f, 0.0f };
	_dir = 1.0f;
}

Hero::~Hero()
{
	if (_animSprite != nullptr)
	{
		delete _animSprite;
	}
}

void Hero::render()
{
	if (_animSprite != nullptr)
	{
		_animSprite->playFrame(_frameNumber);
		if (_dir < 0.0f)
		{
			_animSprite->render(_renderer, true);
		}
		else
		{
			_animSprite->render(_renderer, false);
		}
		
	}
}

void Hero::update(float deltaTime)
{
	
	if (_marioState == SMALL_IDLE)
	{
		_frameNumber = 1;
	}
	else if (_marioState == SMALL_LOOK_UP && _vel.x == 0 && _vel.y == 0)
	{
		_frameNumber = 2;
	}
	else if (_marioState == SMALL_DUCK)
	{
		_frameNumber = 3;
	}
	else if (_marioState == SMALL_WALK)
	{
		_pos.x += _vel.x * deltaTime;
		loopFrame(4, 6);
	}
	else if (_marioState == SMALL_RUN)
	{
		_pos.x += _vel.x * deltaTime;
		loopFrame(7, 9);
	}

	if (_animSprite != nullptr)
	{
		_animSprite->setPositionDst(_pos.x, _pos.y);
	}
}

void Hero::processKeyboard(const uint8_t* state)
{	
	_vel = { 0.0f, 0.0f };

	if (state[SDL_SCANCODE_D])
	{
		_marioState = SMALL_WALK;
		_dir = 1.0f;
		_vel.x += 120.0f * _dir;
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3))
		{
			_marioState = SMALL_RUN;
			_vel.x += MAX_SPEED * _dir;
		}
		
	}
	else if (state[SDL_SCANCODE_A])
	{
		// going left, miroir the texture
		_marioState = SMALL_WALK;
		_dir = -1.0f;
		_vel.x += 120.0f * _dir;
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3))
		{
			_marioState = SMALL_RUN;
			_vel.x += MAX_SPEED * _dir;
		}
	}
	// up/down
	else if (state[SDL_SCANCODE_S])
	{
		_marioState = SMALL_DUCK;
	}
	else if (state[SDL_SCANCODE_W])
	{
		_marioState = SMALL_LOOK_UP;
	}
	else
	{
		_marioState = SMALL_IDLE;
	}
}

void Hero::addAnimatedSpriteComponent(SDL_Renderer* renderer, std::string filepath, int redColorKey, int greenColorKey, int blueColorKey)
{
	_animSprite = new AnimatedSprite(renderer, filepath, redColorKey, greenColorKey, blueColorKey);
}

void Hero::setDimensions(int w, int h)
{
	if (_animSprite != nullptr)
	{
		_animSprite->setDimensionDst(w, h);
	}
}

void Hero::setPosition(float x, float y)
{
	_pos.x = x;
	_pos.y = y;
	if (_animSprite != nullptr)
	{
		_animSprite->setPositionDst(x, y);
	}
}


void Hero::setFrameDimension(int w, int h)
{
	if (_animSprite != nullptr)
	{
		_animSprite->setFrameDimension(w, h);
	}

}

void Hero::setImageGridSize(int i, int j)
{
	if (_animSprite != nullptr)
	{
		_animSprite->setImageGridSize(i, j);
	}
}

void Hero::loopFrame(int firstFrame, int lastFrame)
{
	if (_frameNumber < lastFrame && _frameNumber >= firstFrame)
	{
		_frameNumber++;
	}
	else
	{
		_frameNumber = firstFrame;
	}
}