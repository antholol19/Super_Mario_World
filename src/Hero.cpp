#include "Hero.h"
const float Hero::MAX_SPEED = 162.0f;

Hero::Hero(std::string name) : Entity(name), _name(name)
{
	_animSprite = nullptr;
	_framePos = { 1, 1 };
	_marioState = SMALL_IDLE;
	_pos = { 0.0f, 0.0f };
	_vel = { 0.0f, 0.0f };
	_dir = 1.0f;
}

Hero::~Hero()
{

}

void Hero::update(float deltaTime)
{
	
	if (_marioState == SMALL_IDLE)
	{
		_framePos = { 1, 1 };
	}
	else if (_marioState == SMALL_LOOK_UP && _vel.x == 0 && _vel.y == 0)
	{
		_framePos = { 1, 2 };
	}
	else if (_marioState == SMALL_DUCK)
	{
		_framePos = { 1, 3 };
	}
	else if (_marioState == SMALL_WALK)
	{
		_pos.x += _vel.x * deltaTime;
		loopFrame({ 1, 4 }, { 1, 6 });
	}
	else if (_marioState == SMALL_RUN)
	{
		_pos.x += _vel.x * deltaTime;
		loopFrame({ 1, 7 }, { 1, 9 });
	}

	if (_animSprite != nullptr)
	{
		_animSprite->playFrame(_framePos.row, _framePos.col);
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
		_animSprite->setIsFlipped(false);
		
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
		_animSprite->setIsFlipped(true);
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

void Hero::addAnimatedSpriteComponent(SDL_Renderer* renderer, std::string name, Layer layer, std::string filepath, int redColorKey, int greenColorKey, int blueColorKey)
{
	_animSprite = std::make_shared<AnimatedSpriteComponent>(renderer, filepath, redColorKey, greenColorKey, blueColorKey);
	_animSprite->setLayer(layer);
	ComponentManager::getInstance().addComponent(name, _animSprite);
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

void Hero::setFrames(int i, int j, int w, int h, int gridLineWidth)
{
	if (_animSprite != nullptr)
	{
		_animSprite->setFrames(i, j, w, h, gridLineWidth);
	}
}

void Hero::loopFrame(Grid2D firstFrame, Grid2D lastFrame)
{
	if (_framePos.row < lastFrame.row && _framePos.row >= firstFrame.row)
	{
		_framePos.row++;
	}
	else
	{
		_framePos.row = firstFrame.row;
	}

	if (_framePos.col < lastFrame.col && _framePos.col >= firstFrame.col)
	{
		_framePos.col++;
	}
	else
	{
		_framePos.col = firstFrame.col;
	}
}