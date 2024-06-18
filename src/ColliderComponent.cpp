#include "ColliderComponent.h"
#include <minmax.h>

ColliderComponent::ColliderComponent()
{
	_name = "";
	_colliderRect = new SDL_Rect;
	_colliderRect->x = 0;
	_colliderRect->y = 0;
	_colliderRect->w = 0;
	_colliderRect->h = 0;

}

ColliderComponent::~ColliderComponent()
{

}

void ColliderComponent::update(float deltaTime)
{

}

void ColliderComponent::render(SDL_Renderer* renderer)
{

}

SDL_Rect& ColliderComponent::getColliderBoundingBox()
{
	return *_colliderRect;
}

SDL_bool ColliderComponent::isColliding(ColliderComponent& collider)
{
	if (_colliderRect == nullptr)
	{
		return SDL_FALSE;
	}
	const SDL_Rect* temp = collider._colliderRect;
	if (temp == nullptr)
	{
		return SDL_FALSE;
	}
	return SDL_HasIntersection(_colliderRect, temp);
}

Vec2D ColliderComponent::setBoundingBoxAuto(SDL_Surface* surface, uint8_t r, uint8_t g, uint8_t b)
{
	SDL_LockSurface(surface);
	int w = surface->w;
	int h = surface->h;
	int pitch = surface->pitch; // length of row of pixels in bytes
	int colorchannels = pitch / w;
	uint8_t* pixels = (uint8_t*)surface->pixels;
	SDL_UnlockSurface(surface);

	int xmin = 0;
	int xmax = w;
	int ymin = h;
	int ymax = 0;

	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w * colorchannels; i += colorchannels)
		{
			if (pixels[j * (w * colorchannels) + i + 0] == b &&
				pixels[j * (w * colorchannels) + i + 1] == g &&
				pixels[j * (w * colorchannels) + i + 2] == r)
			{
				// transparent
			}
			else
			{
				// update smallest and largest value of non-tranparent pixels
				xmin = min(i, xmin);
				xmax = max(i, xmax);
				ymin = min(j, ymin);
				ymax = max(j, ymax);
			}
		}
	}

	int scale = (1200 / 300);
	_colliderRect->w = (xmax / colorchannels - xmin / colorchannels) / scale;
	_colliderRect->h = (ymax - ymin) / scale;

	Vec2D result;
	result.x = xmin / (colorchannels * scale);
	result.y = ymin / scale;
	return result;


}

void ColliderComponent::setAbsolutePosition(float x, float y)
{
	_colliderRect->x = static_cast<int>(x);
	_colliderRect->y = static_cast<int>(y);
}

void ColliderComponent::setDimensions(int w, int h)
{
	_colliderRect->w = w;
	_colliderRect->h = h;
}
