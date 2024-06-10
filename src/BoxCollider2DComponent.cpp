#include "BoxCollider2DComponent.h"
#include <minmax.h>

BoxCollider2DComponent::BoxCollider2DComponent()
{
	_colliderRect = new SDL_Rect;
	_colliderRect->x = 0;
	_colliderRect->y = 0;
	_colliderRect->w = 0;
	_colliderRect->h = 0;

}

BoxCollider2DComponent::~BoxCollider2DComponent()
{

}

SDL_Rect& BoxCollider2DComponent::getColliderBoundingBox()
{
	return *_colliderRect;
}

SDL_bool BoxCollider2DComponent::isColliding(BoxCollider2DComponent& collider)
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

Vec2D BoxCollider2DComponent::setBoundingBoxAuto(SDL_Surface* surface, uint8_t r, uint8_t g, uint8_t b)
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

void BoxCollider2DComponent::setAbsolutePosition(float x, float y)
{
	_colliderRect->x = static_cast<int>(x);
	_colliderRect->y = static_cast<int>(y);
}

void BoxCollider2DComponent::setDimensions(int w, int h)
{
	_colliderRect->w = w;
	_colliderRect->h = h;
}
